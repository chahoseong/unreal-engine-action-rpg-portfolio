#include "Combat/SwordmasterComboSystemComponent.h"

USwordmasterComboSystemComponent* USwordmasterComboSystemComponent::FindComboSystemComponent(AActor* Actor)
{
	return Actor ? Actor->FindComponentByClass<USwordmasterComboSystemComponent>() : nullptr;
}

USwordmasterComboSystemComponent::USwordmasterComboSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USwordmasterComboSystemComponent::StartCombo(const FGameplayTag& AttackTag)
{
	LastComboState.AttackTag = AttackTag;
	LastComboState.ComboIndex = 0;
}

void USwordmasterComboSystemComponent::AdvanceCombo(const FGameplayTag& AttackTag)
{
	LastComboState.AttackTag = AttackTag;
	LastComboState.ComboIndex += 1;
	SavedAttackTag = FGameplayTag::EmptyTag;
}

void USwordmasterComboSystemComponent::ChangeCombo(const FGameplayTag& AttackTag, int32 ComboIndex)
{
	LastComboState.AttackTag = AttackTag;
	LastComboState.ComboIndex = ComboIndex;
	SavedAttackTag = FGameplayTag::EmptyTag;
}

int32 USwordmasterComboSystemComponent::GetLastComboIndex() const
{
	return LastComboState.ComboIndex;
}

const FGameplayTag& USwordmasterComboSystemComponent::GetLastComboAttackTag() const
{
	return LastComboState.AttackTag;
}

void USwordmasterComboSystemComponent::SetComboEnabled(bool bEnabled)
{
	bComboEnabled = bEnabled;
}

bool USwordmasterComboSystemComponent::IsComboEnabled() const
{
	return bComboEnabled;
}
