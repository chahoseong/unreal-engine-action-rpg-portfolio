#include "Characters/SwordmasterCharacter.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/SwordmasterAbilitySet.h"
#include "GameplayEffect.h"


ASwordmasterCharacter::ASwordmasterCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

UAbilitySystemComponent* ASwordmasterCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ASwordmasterCharacter::GetAttributeSet() const
{
	return AttributeSet;
}

void ASwordmasterCharacter::InitAbilityActorInfo()
{

}

void ASwordmasterCharacter::ApplyStartupAbilitySet()
{
	if (StartupAbilitySet)
	{
		StartupAbilitySet->GiveToAbilitySystem(AbilitySystemComponent);
	}
}

void ASwordmasterCharacter::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level)
{
	check(IsValid(AbilitySystemComponent));
	check(GameplayEffectClass);

	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data, AbilitySystemComponent);
}
