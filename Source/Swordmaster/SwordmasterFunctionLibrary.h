// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SwordmasterFunctionLibrary.generated.h"

class USwordmasterInputGlobals;
class USwordmasterCombatComponent;
class USwordmasterInventoryManagerComponent;
class USwordmasterEquipmentManagerComponent;
struct FGameplayTag;

class USwordmasterInteractionSubsystem;


UCLASS()
class SWORDMASTER_API USwordmasterFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category="Swordmaster|Input")
	static USwordmasterInputGlobals* GetInputGlobals(UObject* WorldContext);

	UFUNCTION(BlueprintPure, Category="Swordmaster|Combat")
	static USwordmasterCombatComponent* GetCombatComponentFromActor(AActor* Actor);

	UFUNCTION(BlueprintPure, Category="Swordmaster|Inventory")
	static USwordmasterInventoryManagerComponent* GetInventoryManagerFromActor(AActor* Actor);

	UFUNCTION(BlueprintPure, Category="Swordmaster|Equipment")
	static USwordmasterEquipmentManagerComponent* GetEquipmentComponentManager(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category="Swordmaster|Ability System")
	static void AddGameplayTagIfNotContains(AActor* Actor, const FGameplayTag& TagToAdd);

	UFUNCTION(BlueprintCallable, Category="Swordmaster|Ability System")
	static void RemoveGameplayTagIfContains(AActor* Actor, const FGameplayTag& TagToRemove);

	UFUNCTION(BlueprintCallable, Category="Swordmaster|Ability System")
	static bool DoesActorHaveGameplayTag(AActor* Actor, const FGameplayTag& Tag);

	UFUNCTION(BlueprintCallable, Category="Swordmaster|World")
	static USwordmasterInteractionSubsystem* GetInteractionSubsystem(UObject* WorldContext);
};
