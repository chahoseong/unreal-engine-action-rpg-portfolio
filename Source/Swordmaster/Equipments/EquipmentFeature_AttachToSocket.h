#pragma once

#include "CoreMinimal.h"
#include "Equipments/SwordmasterEquipmentFeature.h"
#include "EquipmentFeature_AttachToSocket.generated.h"

UCLASS(DisplayName = "AttachToSocket")
class SWORDMASTER_API UEquipmentFeature_AttachToSocket : public USwordmasterEquipmentFeature
{
	GENERATED_BODY()

public:
	virtual void OnInstanceEquipped(USwordmasterEquipmentInstance* Instance) override;
	virtual void OnInstanceUnequipped(USwordmasterEquipmentInstance* Instance) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> ActorToSpawn;

	UPROPERTY(EditDefaultsOnly)
	FName AttachmentSocketName = NAME_None;

private:
	UPROPERTY()
	TObjectPtr<AActor> SpawnedActor;
};
