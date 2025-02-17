#pragma once

#include "CoreMinimal.h"
#include "Equipments/Weapons/SwordmasterWeaponFeature.h"
#include "WeaponFeature_InputMapping.generated.h"

class USwordmasterInputLocalPlayerSubsystem;
class UInputMappingContext;

UCLASS(DisplayName="InputMapping")
class SWORDMASTER_API UWeaponFeature_InputMapping : public USwordmasterWeaponFeature
{
	GENERATED_BODY()
	
public:
	virtual void OnWeaponEquipped(USwordmasterWeaponInstance* Instance) override;
	virtual void OnWeaponUnequipped(USwordmasterWeaponInstance* Instance) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> InputMapping;
};
