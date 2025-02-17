#include "Characters/SwordmasterCharacterAbilitySet.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"

USwordmasterCharacterAbilitySet::USwordmasterCharacterAbilitySet(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void USwordmasterCharacterAbilitySet::GiveToAbilitySystem(UAbilitySystemComponent* TargetAbilitySystem, UObject* SourceObject) const
{
	check(TargetAbilitySystem);

	for (const TSubclassOf<UGameplayAbility>& AbilityToGrant : GrantedGameplayAbilities)
	{
		if (AbilityToGrant)
		{
			FGameplayAbilitySpec AbilitySpec(AbilityToGrant);
			AbilitySpec.SourceObject = SourceObject;
			TargetAbilitySystem->GiveAbility(AbilitySpec);
		}
	}

	for (const TSubclassOf<UGameplayEffect>& EffectToGrant : GrantedGameplayEffects)
	{
		if (EffectToGrant)
		{
			UGameplayEffect* DefaultObject = EffectToGrant->GetDefaultObject<UGameplayEffect>();
			TargetAbilitySystem->ApplyGameplayEffectToSelf(DefaultObject, 1.0f, TargetAbilitySystem->MakeEffectContext());
		}
	}
}
