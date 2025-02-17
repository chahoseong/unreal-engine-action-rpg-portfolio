#include "Player/SwordmasterPlayerState.h"
#include "AbilitySystem/SwordmasterAbilitySystemComponent.h"
#include "AbilitySystem/SwordmasterAttributeSet.h"
#include "Inventory/SwordmasterInventoryManagerComponent.h"

ASwordmasterPlayerState::ASwordmasterPlayerState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilitySystemComponent = CreateDefaultSubobject<USwordmasterAbilitySystemComponent>(TEXT("AbilitySystem"));
	AttributeSet = CreateDefaultSubobject<USwordmasterAttributeSet>(TEXT("AttributeSet"));
	InventoryManager = CreateDefaultSubobject<USwordmasterInventoryManagerComponent>(TEXT("InventoryManager"));
}

UAbilitySystemComponent* ASwordmasterPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ASwordmasterPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}

int32 ASwordmasterPlayerState::GetLevel() const
{
	return Level;
}

USwordmasterInventoryManagerComponent* ASwordmasterPlayerState::GetInventory() const
{
	return InventoryManager;
}
