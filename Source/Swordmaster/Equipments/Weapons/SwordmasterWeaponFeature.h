#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SwordmasterWeaponFeature.generated.h"

class USwordmasterWeaponInstance;

UCLASS(Abstract, EditInlineNew, CollapseCategories, DefaultToInstanced)
class SWORDMASTER_API USwordmasterWeaponFeature : public UObject
{
	GENERATED_BODY()

public:
	virtual void OnWeaponEquipped(USwordmasterWeaponInstance* Instance);
	virtual void OnWeaponUnequipped(USwordmasterWeaponInstance* Instance);
};