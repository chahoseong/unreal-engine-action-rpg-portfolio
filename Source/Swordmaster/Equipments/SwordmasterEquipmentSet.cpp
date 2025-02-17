#include "Equipments/SwordmasterEquipmentSet.h"
#include "Equipments/SwordmasterEquipmentInstance.h"

TSubclassOf<USwordmasterEquipmentInstance> USwordmasterEquipmentSet::Find(int ItemId) const
{
	for (const TSubclassOf<USwordmasterEquipmentInstance>& Class : EquipmentClasses)
	{
		const USwordmasterEquipmentInstance* DefaultObject = Class->GetDefaultObject<USwordmasterEquipmentInstance>();
		if (DefaultObject->GetItemId() == ItemId)
		{
			return Class;
		}
	}

	return nullptr;
}
