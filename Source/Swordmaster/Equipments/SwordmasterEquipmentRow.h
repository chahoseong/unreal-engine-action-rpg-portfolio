#pragma once

#include "CoreMinimal.h"
#include "SwordmasterEquipmentRow.generated.h"

class USwordmasterEquipmentInstance;

USTRUCT(Blueprintable, BlueprintType, DisplayName="Swordmaster Equipment")
struct SWORDMASTER_API FSwordmasterEquipmentRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int32 ItemId;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USwordmasterEquipmentInstance> EquipmentClass;
};
