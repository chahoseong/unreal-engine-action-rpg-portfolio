#pragma once

#include "CoreMinimal.h"
#include "Equipments/SwordmasterEquipmentFeature.h"
#include "GameplayTagContainer.h"
#include "EquipmentFeature_ChangeToCharacterParts.generated.h"

USTRUCT()
struct FEquipmentPart
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FGameplayTag Tag;

	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<USkeletalMesh>> Meshes;
};

UCLASS(DisplayName="ChangeToCharacterParts")
class SWORDMASTER_API UEquipmentFeature_ChangeToCharacterParts : public USwordmasterEquipmentFeature
{
	GENERATED_BODY()
	
public:
	virtual void OnInstanceEquipped(USwordmasterEquipmentInstance* Instance) override;
	virtual void OnInstanceUnequipped(USwordmasterEquipmentInstance* Instance) override;

protected:
	UPROPERTY(EditDefaultsOnly, Meta=(TitleProperty="Tag"))
	TArray<FEquipmentPart> Parts;
};
