#include "AbilitySystem/Abilities/SwordmasterGameplayAbility_MeleeAttack.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Combat/SwordmasterCombatComponent.h"
#include "SwordmasterFunctionLibrary.h"
#include "SwordmasterGameplayTags.h"

//void USwordmasterGameplayAbility_MeleeAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
//{
//	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
//
//	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
//	{			
//		constexpr bool bReplicateEndAbility = true;
//		constexpr bool bWasCancelled = true;
//		EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
//	}
//}

//void USwordmasterGameplayAbility_MeleeAttack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
//{
//	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
//}

USwordmasterCombatComponent* USwordmasterGameplayAbility_MeleeAttack::GetCombatComponentFromActorInfo() const
{
	return USwordmasterCombatComponent::FindCombatComponent(CurrentActorInfo->AvatarActor.Get());
}

bool USwordmasterGameplayAbility_MeleeAttack::HandleDamage(AActor* TargetActor, float Force) const
{
	if (UAbilitySystemComponent* TargetAbilitySystem = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor))
	{
		if (TargetAbilitySystem->HasMatchingGameplayTag(SwordmasterGameplayTags::Character_Status_Invincible))
		{
			return false;
		}

		UAbilitySystemComponent* SourceAbilitySystem = GetAbilitySystemComponentFromActorInfo();

		FGameplayEffectContextHandle ContextHandle = SourceAbilitySystem->MakeEffectContext();
		ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
		ContextHandle.SetAbility(this);

		FGameplayEffectSpecHandle DamageEffectSpecHandle = SourceAbilitySystem->MakeOutgoingSpec(DamageEffectClass, 1.0f, ContextHandle);
		SourceAbilitySystem->ApplyGameplayEffectSpecToTarget(*DamageEffectSpecHandle.Data, TargetAbilitySystem);

		FGameplayEffectSpecHandle ImpactEffectSpecHandle = SourceAbilitySystem->MakeOutgoingSpec(ImpactEffectClass, 1.0f, ContextHandle);
		ImpactEffectSpecHandle.Data->SetSetByCallerMagnitude(SwordmasterGameplayTags::Attribute_Combat_Knockdown, Force);
		SourceAbilitySystem->ApplyGameplayEffectSpecToTarget(*ImpactEffectSpecHandle.Data, TargetAbilitySystem);

		return true;
	}

	return false;
}
