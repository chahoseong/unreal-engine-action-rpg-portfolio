#include "Player/SwordmasterPlayerController.h"
#include "Player/SwordmasterPlayerState.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/SwordmasterAbilitySystemComponent.h"
#include "Characters/SwordmasterPlayerCharacter.h"
#include "Combat/SwordmasterCombatTarget.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/InputSettings.h"
#include "GameFramework/SpringArmComponent.h"
#include "Input/SwordmasterInputComponent.h"
#include "Input/SwordmasterInputGlobals.h"
#include "SwordmasterFunctionLibrary.h"
#include "SwordmasterGameplayTags.h"
#include "UI/SwordmasterHUD.h"

ASwordmasterPlayerController::ASwordmasterPlayerController()
	: TeamId(FGenericTeamId(0))
{
}

void ASwordmasterPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(DefaultInputMapping);

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		USwordmasterInputGlobals* InputGlobals = USwordmasterFunctionLibrary::GetInputGlobals(this);
		int32 Priority = InputGlobals ? InputGlobals->GetDefaultInputMappingPriority() : 0;
		Subsystem->AddMappingContext(DefaultInputMapping, Priority);
	}

	USwordmasterInputComponent* SwordmasterInput = CastChecked<USwordmasterInputComponent>(InputComponent);
	
	SwordmasterInput->BindNativeAction(InputConfig, SwordmasterGameplayTags::Input_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move, false);
	SwordmasterInput->BindNativeAction(InputConfig, SwordmasterGameplayTags::Input_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look, false);
	SwordmasterInput->BindNativeAction(InputConfig, SwordmasterGameplayTags::Input_SwitchTarget, ETriggerEvent::Triggered, this, &ThisClass::Input_SwitchTarget_Triggered, false);
	SwordmasterInput->BindNativeAction(InputConfig, SwordmasterGameplayTags::Input_SwitchTarget, ETriggerEvent::Completed, this, &ThisClass::Input_SwitchTarget_Completed, false);
	SwordmasterInput->BindAbilityActions(InputConfig, this, &ThisClass::Input_AbilityInputTagPressed, &ThisClass::Input_AbilityInputTagHeld, &ThisClass::Input_AbilityInputTagReleased);
}

void ASwordmasterPlayerController::Input_Move(const FInputActionValue& InputActionValue)
{
	if (ASwordmasterCharacter* ControlledCharacter = GetPawn<ASwordmasterCharacter>())
	{
		UAbilitySystemComponent* AbilitySystem = ControlledCharacter->GetAbilitySystemComponent();
		if (AbilitySystem->HasMatchingGameplayTag(SwordmasterGameplayTags::Gameplay_NativeInputBlocked))
		{
			return;
		}

		const FVector2D MovementInput = InputActionValue.Get<FVector2D>();
		const FRotator Rotation(0.0f, GetControlRotation().Yaw, 0.0f);

		if (MovementInput.X != 0.0f)
		{
			FVector RightDirection = Rotation.RotateVector(FVector::RightVector);
			ControlledCharacter->AddMovementInput(RightDirection, MovementInput.X);
		}

		if (MovementInput.Y != 0.0f)
		{
			FVector ForwardDirection = Rotation.RotateVector(FVector::ForwardVector);
			ControlledCharacter->AddMovementInput(ForwardDirection, MovementInput.Y);
		}
	}
}

void ASwordmasterPlayerController::Input_Look(const FInputActionValue& InputActionValue)
{
	if (ASwordmasterCharacter* ControlledCharacter = GetPawn<ASwordmasterCharacter>())
	{
		const FVector2D AngularInput = InputActionValue.Get<FVector2D>();

		if (AngularInput.X != 0.0f)
		{
			AddYawInput(AngularInput.X);
		}

		if (AngularInput.Y != 0.0f)
		{
			AddPitchInput(AngularInput.Y);
			RotationInput.Pitch = FMath::Clamp(RotationInput.Pitch, CameraMinPitch, CameraMaxPitch);
		}
	}
}

void ASwordmasterPlayerController::Input_SwitchTarget_Triggered(const FInputActionValue& InputActionValue)
{
	SwitchDirection = InputActionValue.Get<FVector2D>();
}

void ASwordmasterPlayerController::Input_SwitchTarget_Completed(const FInputActionValue& InputActionValue)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetPawn(),
		(SwitchDirection.X > 0.0f ?
			SwordmasterGameplayTags::GameplayEvent_SwitchTarget_Right :
			SwordmasterGameplayTags::GameplayEvent_SwitchTarget_Left),
		FGameplayEventData()
	);
}

void ASwordmasterPlayerController::Input_AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (USwordmasterAbilitySystemComponent* SwordmasterAbilitySystem = GetSwordmasterAbilitySystem())
	{
		SwordmasterAbilitySystem->AbilityInputTagPressed(InputTag);
	}
}

void ASwordmasterPlayerController::Input_AbilityInputTagHeld(FGameplayTag InputTag)
{
}

void ASwordmasterPlayerController::Input_AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (USwordmasterAbilitySystemComponent* SwordmasterAbilitySystem = GetSwordmasterAbilitySystem())
	{
		SwordmasterAbilitySystem->AbilityInputTagReleased(InputTag);
	}
}

void ASwordmasterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ASwordmasterHUD* SwordmasterHUD = GetHUD<ASwordmasterHUD>();
	SwordmasterHUD->ShowOverlay();
}

void ASwordmasterPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	if (USwordmasterAbilitySystemComponent* SwordmasterAbilitySystem = GetSwordmasterAbilitySystem())
	{
		SwordmasterAbilitySystem->ProcessAbilityInput(DeltaTime, bGamePaused);
	}

	Super::PostProcessInput(DeltaTime, bGamePaused);
}

void ASwordmasterPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (ASwordmasterPlayerCharacter* ControlledCharacter = GetPawn<ASwordmasterPlayerCharacter>())
	{
		ControlledCharacter->GetSpringArm()->SetRelativeRotation(GetControlRotation());
	}
}

FGenericTeamId ASwordmasterPlayerController::GetGenericTeamId() const
{
	return TeamId;
}

USwordmasterAbilitySystemComponent* ASwordmasterPlayerController::GetSwordmasterAbilitySystem() const
{
	if (ASwordmasterPlayerState* SwordmasterPlayerState = GetPlayerState<ASwordmasterPlayerState>())
	{
		return SwordmasterPlayerState->GetAbilitySystemComponent<USwordmasterAbilitySystemComponent>();
	}
	
	return nullptr;
}
