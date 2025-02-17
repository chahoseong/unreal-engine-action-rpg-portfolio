// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SwordmasterInputGlobals.generated.h"

UCLASS(Blueprintable, Blueprintable)
class SWORDMASTER_API USwordmasterInputGlobals : public UObject
{
	GENERATED_BODY()
	
public:
	int32 GetDefaultInputMappingPriority() const;
	int32 GetWeaponInputMappingPriority() const;
	int32 GetUIInputMappingPriority() const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Priority")
	int32 DefaultInputMappingPriority = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Priority")
	int32 WeaponInputMappingPriority = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Priority")
	int32 UIInputMappingPriority = 2;
};
