#include "AbilitySystem/Abilities/SwordmasterGameplayAbility_TargetLock.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SwordmasterFunctionLibrary.h"
#include "SwordmasterGameplayTags.h"
#include "UI/Widget/SwordmasterUserWidget.h"

void USwordmasterGameplayAbility_TargetLock::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (ACharacter* Character = Cast<ACharacter>(GetAvatarActorFromActorInfo()))
	{
		bCachedOrientRotationToMovement = Character->GetCharacterMovement()->bOrientRotationToMovement;
		Character->GetCharacterMovement()->bOrientRotationToMovement = false;
	}

	TryLockOnTarget();
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void USwordmasterGameplayAbility_TargetLock::TryLockOnTarget()
{
	FindAvailableActorsToLock();

	if (AvailableActorsToLock.IsEmpty())
	{
		CancelTargetLockAbility();
		return;
	}

	CurrentLockedActor = GetNearestTargetFromActors(AvailableActorsToLock);

	if (CurrentLockedActor)
	{
		InitInputMapping();
		ShowIndicatorWidget();
		OnTargetLocked.Broadcast();
	}
	else
	{
		CancelTargetLockAbility();
	}
}

void USwordmasterGameplayAbility_TargetLock::FindAvailableActorsToLock()
{
	AvailableActorsToLock.Empty();

	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	TArray<FHitResult> TraceHits;

	const FVector ControlForward = GetControlForwardVector();
	const FRotator ControlRotation = GetControllerFromActorInfo()->GetControlRotation();

	UKismetSystemLibrary::BoxTraceMultiForObjects(
		AvatarActor,
		AvatarActor->GetActorLocation() + (ControlForward * TraceBoxSize.X * 0.5f),
		AvatarActor->GetActorLocation() + (ControlForward * TraceMaxDistance),
		TraceBoxSize * 0.5f,
		FRotator(0.0f, ControlRotation.Yaw, 0.0f),
		TraceQueryChannel,
		false,
		TArray<AActor*>(),
		(bShowTraceDebug ? EDrawDebugTrace::Persistent : EDrawDebugTrace::None),
		TraceHits,
		true
	);

	for (const FHitResult& HitResult : TraceHits)
	{
		if (AActor* Actor = HitResult.GetActor())
		{
			AvailableActorsToLock.AddUnique(Actor);
		}
	}
}

AActor* USwordmasterGameplayAbility_TargetLock::GetNearestTargetFromActors(const TArray<AActor*>& Actors)
{
	float ClosestDistance = 0.0f;
	return UGameplayStatics::FindNearestActor(GetAvatarActorFromActorInfo()->GetActorLocation(), Actors, ClosestDistance);
}

void USwordmasterGameplayAbility_TargetLock::InitInputMapping()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(GetControllerFromActorInfo()))
	{
		const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

		check(Subsystem);

		Subsystem->AddMappingContext(InputMapping, 3);
	}
}

void USwordmasterGameplayAbility_TargetLock::ShowIndicatorWidget()
{
	if (ActiveIndicatorWidget)
	{
		ActiveIndicatorWidget->SetVisibility(ESlateVisibility::Visible);
		return;
	}
	ActiveIndicatorWidget = CreateWidget<USwordmasterUserWidget>(GetWorld(), IndicatorWidgetClass);
	ActiveIndicatorWidget->SetController(this);
	ActiveIndicatorWidget->AddToViewport();
}

void USwordmasterGameplayAbility_TargetLock::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	ResetInputMapping();
	HideIndicatorWidget();

	if (ACharacter* Character = Cast<ACharacter>(GetAvatarActorFromActorInfo()))
	{
		Character->GetCharacterMovement()->bOrientRotationToMovement = bCachedOrientRotationToMovement;
	}

	AvailableActorsToLock.Empty();
	CurrentLockedActor = nullptr;

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void USwordmasterGameplayAbility_TargetLock::ResetInputMapping()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(GetControllerFromActorInfo()))
	{
		const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

		check(Subsystem);

		Subsystem->RemoveMappingContext(InputMapping);
	}
}

void USwordmasterGameplayAbility_TargetLock::HideIndicatorWidget()
{
	if (ActiveIndicatorWidget)
	{
		ActiveIndicatorWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void USwordmasterGameplayAbility_TargetLock::UpdateTargetLock(float DeltaTime)
{
	// Early Return Case 1: Invalid Current Locked Actor.
	if (!CurrentLockedActor)
	{
		CancelTargetLockAbility();
		return;
	}

	// Early Return Case 2: Current Locked Actor or Avatar Actor is Dead.
	const bool bIsCurrentLockedActorDead = USwordmasterFunctionLibrary::DoesActorHaveGameplayTag(CurrentLockedActor, SwordmasterGameplayTags::Character_Status_Dead);
	const bool bIsAvatarActorDead = USwordmasterFunctionLibrary::DoesActorHaveGameplayTag(GetAvatarActorFromActorInfo(), SwordmasterGameplayTags::Character_Status_Dead);
	if (bIsCurrentLockedActorDead || bIsAvatarActorDead)
	{
		CancelTargetLockAbility();
		return;
	}

	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	const bool bIsRolling = USwordmasterFunctionLibrary::DoesActorHaveGameplayTag(AvatarActor, SwordmasterGameplayTags::Character_Status_Rolling);

	if (!bIsRolling)
	{
		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(
			AvatarActor->GetActorLocation(),
			CurrentLockedActor->GetActorLocation()
		);

		TargetRotation += FRotator(ViewPitchOffset, 0.0f, 0.0f);

		AController* Controller = GetControllerFromActorInfo();
		const FRotator CurrentControlRotation = Controller->GetControlRotation();
		const FRotator ControlRotationStep = FMath::RInterpTo(CurrentControlRotation, TargetRotation, DeltaTime, RotationSpeed);
		Controller->SetControlRotation(FRotator(ControlRotationStep.Pitch, ControlRotationStep.Yaw, 0.0f));

		if (bShouldActorRotateTowardsTarget)
		{
			FVector ToTarget = (CurrentLockedActor->GetActorLocation() - AvatarActor->GetActorLocation()).GetSafeNormal();
			float DotResult = AvatarActor->GetActorForwardVector().Dot(ToTarget);

			if (DotResult >= 0.95f)
			{
				bShouldActorRotateTowardsTarget = false;
			}
			else
			{
				const FRotator ActorRotationStep = FMath::RInterpTo(AvatarActor->GetActorRotation(), TargetRotation, DeltaTime, RotationSpeed);
				AvatarActor->SetActorRotation(FRotator(0.0f, ActorRotationStep.Yaw, 0.0f));
			}
		}
		else
		{
			AvatarActor->SetActorRotation(FRotator(0.0f, ControlRotationStep.Yaw, 0.0f));
		}
	}
	else
	{
		bShouldActorRotateTowardsTarget = true;
	}

	OnTick.Broadcast();
}

void USwordmasterGameplayAbility_TargetLock::SwitchTarget(const FGameplayTag& DirectionTag)
{
	FindAvailableActorsToLock();

	TArray<AActor*> ActorsOnLeft;
	TArray<AActor*> ActorsOnRight;
	DivideAvailableActorsOnDirection(ActorsOnLeft, ActorsOnRight);

	AActor* NewTargetToLock = nullptr;
	if (DirectionTag == SwordmasterGameplayTags::GameplayEvent_SwitchTarget_Left)
	{
		NewTargetToLock = GetNearestTargetFromActors(ActorsOnLeft);
	}
	else
	{
		NewTargetToLock = GetNearestTargetFromActors(ActorsOnRight);
	}

	if (NewTargetToLock)
	{
		CurrentLockedActor = NewTargetToLock;
	}
}

void USwordmasterGameplayAbility_TargetLock::DivideAvailableActorsOnDirection(TArray<AActor*>& ActorsOnLeft, TArray<AActor*>& ActorsOnRight)
{
	AActor* AvatarActor = GetAvatarActorFromActorInfo();

	FVector BaseDirection = (CurrentLockedActor->GetActorLocation() - AvatarActor->GetActorLocation()).GetSafeNormal();

	for (AActor* Target : AvailableActorsToLock)
	{
		if (CurrentLockedActor != Target)
		{
			FVector ToTarget = (Target->GetActorLocation() - AvatarActor->GetActorLocation()).GetSafeNormal();
			FVector CrossResult = BaseDirection.Cross(ToTarget);

			if (CrossResult.Z > 0)
			{
				ActorsOnRight.Add(Target);
			}
			else
			{
				ActorsOnLeft.Add(Target);
			}
		}
	}
}

FVector USwordmasterGameplayAbility_TargetLock::GetControlForwardVector() const
{
	FVector ControlForward;

	if (AController* Controller = GetControllerFromActorInfo())
	{
		FRotationMatrix ControlRotation = GetControllerFromActorInfo()->GetControlRotation();
		ControlForward = ControlRotation.TransformVector(FVector::ForwardVector);
		ControlForward.Z = 0.0f;
	}

	return ControlForward;
}

void USwordmasterGameplayAbility_TargetLock::CancelTargetLockAbility()
{
	CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
}
