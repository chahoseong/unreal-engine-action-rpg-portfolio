// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "SwordmasterInteractionSubsystem.generated.h"

class USwordmasterInteractionDefinition;

UCLASS()
class SWORDMASTER_API USwordmasterInteractionSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	USwordmasterInteractionDefinition* GetInteraction(TSubclassOf<USwordmasterInteractionDefinition> Class) const;

protected:
	UPROPERTY()
	mutable TMap<UClass*, TObjectPtr<USwordmasterInteractionDefinition>> CachedInteractions;
};
