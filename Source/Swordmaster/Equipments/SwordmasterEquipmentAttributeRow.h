#pragma once

#include "CoreMinimal.h"
#include "SwordmasterEquipmentAttributeRow.generated.h"

USTRUCT(Blueprintable, BlueprintType, DisplayName="Equipment Attribute")
struct SWORDMASTER_API FSwordmasterEquipmentAttributeRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Equipment")
	int32 ItemId;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Equipment|Attributes")
	float Strength;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Equipment|Attributes")
	float Intellect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Equipment|Attributes")
	float Agility;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Equipment|Attributes")
	float Will;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Equipment|Attributes")
	float MaxHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Equipment|Attributes")
	float MaxStamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Equipment|Attributes")
	float WeaponDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Equipment|Attributes")
	float Armor;
};
