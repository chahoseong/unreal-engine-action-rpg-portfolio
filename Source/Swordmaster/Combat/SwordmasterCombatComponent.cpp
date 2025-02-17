#include "Combat/SwordmasterCombatComponent.h"
#include "Combat/SwordmasterCombatTarget.h"
#include "Combat/SwordmasterCombatWeapon.h"
#include "Combat/SwordmasterCombatFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/SwordmasterAttributeSet.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Engine/OverlapResult.h"
#include "Kismet/KismetMathLibrary.h"
#include "SwordmasterGameplayTags.h"

#include "DrawDebugHelpers.h"

USwordmasterCombatComponent* USwordmasterCombatComponent::FindCombatComponent(AActor* Actor)
{
	return Actor ? Actor->FindComponentByClass<USwordmasterCombatComponent>() : nullptr;
}

USwordmasterCombatComponent::USwordmasterCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USwordmasterCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bWeaponDamageEnabled)
	{
		if (const UWorld* World = GEngine->GetWorldFromContextObject(GetOwner(), EGetWorldErrorMode::LogAndReturnNull))
		{
			TArray<FOverlapResult> Overlaps;
			World->OverlapMultiByObjectType(
				Overlaps,
				HitBoxLocation,
				GetOwner()->GetActorQuat(),
				FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects),
				FCollisionShape::MakeBox(ISwordmasterCombatWeapon::Execute_GetAttackBoundary(CurrentWeapon.GetObject())),
				HitBoxQueryParams
			);

			TSet<AActor*> ActorSet;
			for (FOverlapResult& Overlap : Overlaps)
			{
				AActor* Actor = Overlap.GetActor();

				if (IsDead(Actor))
				{
					continue;
				}

				// 공격이 어떤 대상에게 막혔다면,
				// 그 후에는 더이상 공격 절차를 진행하지 않습니다.
				float AttackBlockedCost = 0.0f;
				if (IsAttackParried(Actor) || IsAttackBlocked(Actor, AttackBlockedCost))
				{
					SetWeaponDamageEnabled(false);

					FGameplayEventData Payload;
					Payload.Target = GetOwner();
					Payload.EventMagnitude = AttackBlockedCost;
					UE_LOG(LogTemp, Warning, TEXT("Attack Blocked Cost: %f"), AttackBlockedCost);
					UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
						Actor,
						SwordmasterGameplayTags::GameplayEvent_AttackBlocked,
						Payload
					);

					break;
				}

				ActorSet.Add(Actor);
			}

			TArray<AActor*> ActorList = ActorSet.Array();

			TArray<TWeakObjectPtr<AActor>> TargetActors;
			Algo::Transform(ActorList, TargetActors, [](AActor* Actor) { return TWeakObjectPtr<AActor>(Actor); });

			FGameplayAbilityTargetData_ActorArray* TargetData = new FGameplayAbilityTargetData_ActorArray();
			TargetData->SetActors(TargetActors);

			FGameplayEventData Payload;
			Payload.TargetData = FGameplayAbilityTargetDataHandle(TargetData);
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
				GetOwner(),
				SwordmasterGameplayTags::GameplayEvent_AttackHit,
				Payload
			);

			HitBoxQueryParams.AddIgnoredActors(ActorList);
		}
	}
}

bool USwordmasterCombatComponent::IsDead(AActor* Actor) const
{
	if (Actor->GetClass()->ImplementsInterface(USwordmasterCombatTarget::StaticClass()))
	{
		return ISwordmasterCombatTarget::Execute_IsDead(Actor);
	}
	return true;
}

bool USwordmasterCombatComponent::IsAttackParried(AActor* Actor) const
{
	if (UAbilitySystemComponent* AbilitySystem = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor))
	{
		return AbilitySystem->HasMatchingGameplayTag(SwordmasterGameplayTags::Character_Status_Parryable);
	}

	return false;
}

bool USwordmasterCombatComponent::IsAttackBlocked(AActor* Actor, float& Cost) const
{
	UAbilitySystemComponent* TargetAbilitySystem = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor);
	UAbilitySystemComponent* OwningAbilitySystem = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner());

	if (TargetAbilitySystem && OwningAbilitySystem)
	{
		if (TargetAbilitySystem->HasMatchingGameplayTag(SwordmasterGameplayTags::Character_Status_Defending))
		{
			const FVector OwnerForward = GetOwner()->GetActorForwardVector();
			const FVector TargetForward = Actor->GetActorForwardVector();

			const float DotResult = FVector::DotProduct(OwnerForward, -TargetForward);
			UE_LOG(LogTemp, Warning, TEXT("Dot Result: %f, Max: %f"), DotResult, UKismetMathLibrary::DegCos(DefensibleMaxAngle));
			if (DotResult >= UKismetMathLibrary::DegCos(DefensibleMaxAngle))
			{
				bool bFoundAttribute = false;

				float SourceWeaponDamage = OwningAbilitySystem->GetGameplayAttributeValue(USwordmasterAttributeSet::GetWeaponDamageAttribute(), bFoundAttribute);
				float SourceStrength = OwningAbilitySystem->GetGameplayAttributeValue(USwordmasterAttributeSet::GetStrengthAttribute(), bFoundAttribute);

				FAttackDamageParameters Params{ SourceWeaponDamage, SourceStrength };
				float SourceDamage = USwordmasterCombatFunctionLibrary::CalculateAttackDamage(Params);

				float TargetBlockedDamageReduction = TargetAbilitySystem->GetGameplayAttributeValue(USwordmasterAttributeSet::GetBlockedDamageReductionAttribute(), bFoundAttribute);
				float ReducedSourceDamage = SourceDamage * TargetBlockedDamageReduction;

				float TargetStamina = TargetAbilitySystem->GetGameplayAttributeValue(USwordmasterAttributeSet::GetStaminaAttribute(), bFoundAttribute);
				if (TargetStamina >= ReducedSourceDamage)
				{
					Cost = -ReducedSourceDamage;
					return true;
				}
			}
		}
	}

	return false;
}

void USwordmasterCombatComponent::SetWeapon(TScriptInterface<ISwordmasterCombatWeapon> NewWeapon)
{
	CurrentWeapon = NewWeapon;
}

void USwordmasterCombatComponent::SetWeaponDamageEnabled(bool bEnabled)
{
	if (bEnabled)
	{
		AActor* OwningActor = GetOwner();
		HitBoxLocation = OwningActor->GetActorLocation() +
			OwningActor->GetActorForwardVector() * HitBoxOffset.X +
			OwningActor->GetActorRightVector() * HitBoxOffset.Y +
			OwningActor->GetActorUpVector() * HitBoxOffset.Z;
		HitBoxQueryParams.ClearIgnoredActors();
		HitBoxQueryParams.AddIgnoredActor(OwningActor);
	}

	bWeaponDamageEnabled = bEnabled;
}

void USwordmasterCombatComponent::DrawDebugHitBox()
{
	if (bWeaponDamageEnabled && CurrentWeapon.GetObject())
	{
		AActor* OwningActor = GetOwner();
		FVector DebugHitBoxOrigin = OwningActor->GetActorLocation() +
			OwningActor->GetActorForwardVector() * HitBoxOffset.X +
			OwningActor->GetActorRightVector() * HitBoxOffset.Y +
			OwningActor->GetActorUpVector() * HitBoxOffset.Z;

		DrawDebugBox(
			GetWorld(),
			DebugHitBoxOrigin,
			ISwordmasterCombatWeapon::Execute_GetAttackBoundary(CurrentWeapon.GetObject()),
			OwningActor->GetActorQuat(),
			FColor::Red,
			false,
			-1.0f,
			0,
			1.0f
		);
	}
}
