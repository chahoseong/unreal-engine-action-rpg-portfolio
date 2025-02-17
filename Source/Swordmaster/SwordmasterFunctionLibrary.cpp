#include "SwordmasterFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Combat/SwordmasterCombatInterface.h"
#include "Combat/SwordmasterCombatComponent.h"
#include "Engine/World.h"
#include "Equipments/SwordmasterEquipmentManagerComponent.h"
#include "GenericTeamAgentInterface.h"
#include "Inventory/SwordmasterInventoryManagerComponent.h"
#include "Player/SwordmasterPlayerState.h"
#include "System/SwordmasterGameInstance.h"
#include "System/SwordmasterInteractionSubsystem.h"

USwordmasterInputGlobals* USwordmasterFunctionLibrary::GetInputGlobals(UObject* WorldContext)
{
	if (GEngine)
	{
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::LogAndReturnNull))
		{
			USwordmasterGameInstance* SwordmasterGameInstance = World->GetGameInstance<USwordmasterGameInstance>();
			return SwordmasterGameInstance->GetInputGlobals();
		}
	}

	return nullptr;
}

USwordmasterCombatComponent* USwordmasterFunctionLibrary::GetCombatComponentFromActor(AActor* Actor)
{
	if (ISwordmasterCombatInterface* CombatInterface = Cast<ISwordmasterCombatInterface>(Actor))
	{
		return CombatInterface->GetSwordmasterCombatComponent();
	}

	if (Actor)
	{
		if (USwordmasterCombatComponent* CombatComponent = Actor->GetComponentByClass<USwordmasterCombatComponent>())
		{
			return CombatComponent;
		}
	}

	return nullptr;
}

USwordmasterInventoryManagerComponent* USwordmasterFunctionLibrary::GetInventoryManagerFromActor(AActor* Actor)
{
	if (USwordmasterInventoryManagerComponent* InventoryManager = Actor->GetComponentByClass<USwordmasterInventoryManagerComponent>())
	{
		return InventoryManager;
	}

	if (APawn* Pawn = Cast<APawn>(Actor))
	{
		if (ASwordmasterPlayerState* PlayerState = Pawn->GetPlayerState<ASwordmasterPlayerState>())
		{
			return PlayerState->GetInventory();
		}
	}

	return nullptr;
}

USwordmasterEquipmentManagerComponent* USwordmasterFunctionLibrary::GetEquipmentComponentManager(AActor* Actor)
{
	if (USwordmasterEquipmentManagerComponent* EquipmentManager = Actor->GetComponentByClass<USwordmasterEquipmentManagerComponent>())
	{
		return EquipmentManager;
	}
	return nullptr;
}

void USwordmasterFunctionLibrary::AddGameplayTagIfNotContains(AActor* Actor, const FGameplayTag& TagToAdd)
{
	if (UAbilitySystemComponent* AbilitySystem = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor))
	{
		if (!AbilitySystem->HasMatchingGameplayTag(TagToAdd))
		{
			AbilitySystem->AddLooseGameplayTag(TagToAdd);
		}
	}
}

void USwordmasterFunctionLibrary::RemoveGameplayTagIfContains(AActor* Actor, const FGameplayTag& TagToRemove)
{
	if (UAbilitySystemComponent* AbilitySystem = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor))
	{
		if (AbilitySystem->HasMatchingGameplayTag(TagToRemove))
		{
			AbilitySystem->RemoveLooseGameplayTag(TagToRemove);
		}
	}
}

bool USwordmasterFunctionLibrary::DoesActorHaveGameplayTag(AActor* Actor, const FGameplayTag& Tag)
{
	if (UAbilitySystemComponent* AbilitySystem = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor))
	{
		return AbilitySystem->HasMatchingGameplayTag(Tag);
	}
	return false;
}

USwordmasterInteractionSubsystem* USwordmasterFunctionLibrary::GetInteractionSubsystem(UObject* WorldContext)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::LogAndReturnNull))
	{
		return World->GetSubsystem<USwordmasterInteractionSubsystem>();
	}
	return nullptr;
}
