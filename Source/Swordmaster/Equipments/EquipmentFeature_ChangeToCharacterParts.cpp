#include "Equipments/EquipmentFeature_ChangeToCharacterParts.h"
#include "Equipments/SwordmasterEquipmentInstance.h"
#include "Equipments/SwordmasterEquipmentManagerComponent.h"
#include "Characters/SwordmasterCharacterPartsManagerComponent.h"

void UEquipmentFeature_ChangeToCharacterParts::OnInstanceEquipped(USwordmasterEquipmentInstance* Instance)
{
	USwordmasterEquipmentManagerComponent* EquipmentManager = Cast<USwordmasterEquipmentManagerComponent>(Instance->GetOuter());
	check(EquipmentManager);

	USwordmasterCharacterPartsManagerComponent* CharacterPartsManager = EquipmentManager->GetOwner()->GetComponentByClass<USwordmasterCharacterPartsManagerComponent>();
	for (const FEquipmentPart& Part : Parts)
	{
		CharacterPartsManager->ChangeCurrentPart(Part.Tag, Part.Meshes);
	}
}

void UEquipmentFeature_ChangeToCharacterParts::OnInstanceUnequipped(USwordmasterEquipmentInstance* Instance)
{
	USwordmasterEquipmentManagerComponent* EquipmentManager = Cast<USwordmasterEquipmentManagerComponent>(Instance->GetOuter());
	check(EquipmentManager);

	USwordmasterCharacterPartsManagerComponent* CharacterPartsManager = EquipmentManager->GetOwner()->GetComponentByClass<USwordmasterCharacterPartsManagerComponent>();
	for (const FEquipmentPart& Part : Parts)
	{
		CharacterPartsManager->RemoveCurrentPart(Part.Tag);
	}
}
