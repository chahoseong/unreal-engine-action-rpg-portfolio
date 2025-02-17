#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SwordmasterEquipmentFeature.generated.h"

class USwordmasterEquipmentInstance;

UCLASS(Abstract, EditInlineNew, CollapseCategories, DefaultToInstanced)
class SWORDMASTER_API USwordmasterEquipmentFeature : public UObject
{
	GENERATED_BODY()

public:
	virtual void OnInstanceEquipped(USwordmasterEquipmentInstance* Instance);
	virtual void OnInstanceUnequipped(USwordmasterEquipmentInstance* Instance);
};
