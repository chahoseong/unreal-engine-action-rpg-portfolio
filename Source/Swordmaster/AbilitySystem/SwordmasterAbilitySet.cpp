#include "AbilitySystem/SwordmasterAbilitySet.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "SwordmasterLogChannels.h"

/*
 * FSwordmasterAbilitySet_GrantedHandles
 */

void FSwordmasterAbilitySet_GrantedHandles::AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle)
{
	if (Handle.IsValid())
	{
		AbilitySpecHandles.Add(Handle);
	}
}

void FSwordmasterAbilitySet_GrantedHandles::AddEffectSpecHandle(const FActiveGameplayEffectHandle& Handle)
{
	if (Handle.IsValid())
	{
		EffectSpecHandles.Add(Handle);
	}
}

void FSwordmasterAbilitySet_GrantedHandles::Reset(UAbilitySystemComponent* AbilitySystem)
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
 * USwordmasterAbilitySet
 */

USwordmasterAbilitySet::USwordmasterAbilitySet(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FSwordmasterAbilitySet_GrantedHandles USwordmasterAbilitySet::GiveToAbilitySystem(UAbilitySystemComponent* TargetAbilitySystem, UObject* SourceObject) const
{
	check(TargetAbilitySystem);

	FSwordmasterAbilitySet_GrantedHandles GrantedHandles;

	// GrantedGameplayAbilities
	for (int32 AbilityIndex = 0; AbilityIndex < GrantedGameplayAbilities.Num(); ++AbilityIndex)
	{
		const TSubclassOf<UGameplayAbility>& AbilityToGrant = GrantedGameplayAbilities[AbilityIndex];

		if (!IsValid(AbilityToGrant))
		{
			UE_LOG(LogSwordmasterAbilitySystem, Error, TEXT("GrantedGameplayAbilities[%d] on ability set [%s] is not valid."), AbilityIndex, *GetNameSafe(this));
			continue;
		}
		
		FGameplayAbilitySpec AbilitySpec(AbilityToGrant);
		AbilitySpec.SourceObject = SourceObject;

		FGameplayAbilitySpecHandle Handle = TargetAbilitySystem->GiveAbility(AbilitySpec);
		GrantedHandles.AddAbilitySpecHandle(Handle);
	}

	// GrantedGameplayAbilitiesWithInputTags
	for (int32 AbilityIndex = 0; AbilityIndex < GrantedGameplayAbilitiesWithInputTags.Num(); ++AbilityIndex)
	{
		const FSwordmasterAbilitySet_GameplayAbilityWithInputTag& AbilityToGrant = GrantedGameplayAbilitiesWithInputTags[AbilityIndex];

		if (!IsValid(AbilityToGrant.Ability))
		{
			UE_LOG(LogSwordmasterAbilitySystem, Error, TEXT("GrantedGameplayAbilitiesWithInputTags[%d] on ability set [%s] is not valid."), AbilityIndex, *GetNameSafe(this));
			continue;
		}

		FGameplayAbilitySpec AbilitySpec(AbilityToGrant.Ability);
		AbilitySpec.SourceObject = SourceObject;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilityToGrant.InputTag);

		FGameplayAbilitySpecHandle Handle = TargetAbilitySystem->GiveAbility(AbilitySpec);
		GrantedHandles.AddAbilitySpecHandle(Handle);
	}

	// GrantedGameplayEffects
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
