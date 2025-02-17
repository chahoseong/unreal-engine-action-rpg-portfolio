#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SwordmasterEquipmentSet.generated.h"

class USwordmasterEquipmentInstance;

UCLASS(Blueprintable, BlueprintType, Const)
class SWORDMASTER_API USwordmasterEquipmentSet : public UDataAsset
{
	GENERATED_BODY()
	
public:
	TSubclassOf<USwordmasterEquipmentInstance> Find(int ItemId) const;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Swordmaster")
	TArray<TSubclassOf<USwordmasterEquipmentInstance>> EquipmentClasses;
};
