#include "Equipments/Weapons/SwordmasterWeaponAbilitySet.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "SwordmasterLogChannels.h"

/*
 * FSwordmasterWeaponAbilitySet_GrantedHandles
 */

void FSwordmasterWeaponAbilitySet_GrantedHandles::AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle)
{
	if (Handle.IsValid())
	{
		AbilitySpecHandles.Add(Handle);
	}
}

void FSwordmasterWeaponAbilitySet_GrantedHandles::AddEffectSpecHandle(const FActiveGameplayEffectHandle& Handle)
{
	if (Handle.IsValid())
	{
		EffectSpecHandles.Add(Handle);
	}
}

void FSwordmasterWeaponAbilitySet_GrantedHandles::Reset(UAbilitySystemComponent* AbilitySystem)
{
	check(AbilitySystem);

	for (const FGameplayAbilitySpecHandle& Handle : AbilitySpecHandles)
	{
		if (Handle.IsValid())
		{
			AbilitySystem->ClearAbility(Handle);
		}
	}

	for (const FActiveGameplayEffectHandle& Handle : EffectSpecHandles)
	{
		if (Handle.IsValid())
		{
			AbilitySystem->RemoveActiveGameplayEffect(Handle);
		}
	}

	AbilitySpecHandles.Reset();
	EffectSpecHandles.Reset();
}

/*
 * USwordmasterWeaponAbilitySet
 */

USwordmasterWeaponAbilitySet::USwordmasterWeaponAbilitySet(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FSwordmasterWeaponAbilitySet_GrantedHandles USwordmasterWeaponAbilitySet::GiveToAbilitySystem(UAbilitySystemComponent* TargetAbilitySystem, UObject* SourceObject) const
{
	check(TargetAbilitySystem);

	FSwordmasterWeaponAbilitySet_GrantedHandles GrantedHandles;

	for (int32 AbilityIndex = 0; AbilityIndex < GrantedGameplayAbilities.Num(); ++AbilityIndex)
	{
		const FSwordmasterWeaponAbilitySet_GameplayAbility& AbilityToGrant = GrantedGameplayAbilities[AbilityIndex];

		if (!IsValid(AbilityToGrant.Ability))
		{
			UE_LOG(LogSwordmasterAbilitySystem, Error, TEXT("GrantedGameplayAbilities[%d] on ability set [%s] is not valid."), AbilityIndex, *GetNameSafe(this));
			continue;
		}

		FGameplayAbilitySpec AbilitySpec(AbilityToGrant.Ability);
		AbilitySpec.SourceObject = SourceObject;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilityToGrant.InputTag);

		FGameplayAbilitySpecHandle Handle = TargetAbilitySystem->GiveAbility(AbilitySpec);
		GrantedHandles.AddAbilitySpecHandle(Handle);
	}

	for (const TSubclassOf<UGameplayEffect>& EffectToGrant : GrantedGameplayEffects)
	{
		if (EffectToGrant)
		{
			UGameplayEffect* DefaultObject = EffectToGrant->GetDefaultObject<UGameplayEffect>();
			FActiveGameplayEffectHandle Handle = TargetAbilitySystem->ApplyGameplayEffectToSelf(DefaultObject, 1.0f, TargetAbilitySystem->MakeEffectContext());
			GrantedHandles.AddEffectSpecHandle(Handle);
		}
	}

	return GrantedHandles;
}
