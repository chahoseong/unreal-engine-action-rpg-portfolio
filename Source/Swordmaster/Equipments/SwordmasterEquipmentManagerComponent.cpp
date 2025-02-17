#include "Equipments/SwordmasterEquipmentManagerComponent.h"
#include "Equipments/SwordmasterEquipmentInstance.h"
#include "Equipments/SwordmasterEquipmentRow.h"
#include "Engine/AssetManager.h"
#include "SwordmasterGameplayTags.h"
#include "SwordmasterDataTableHelper.h"

USwordmasterEquipmentManagerComponent::USwordmasterEquipmentManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USwordmasterEquipmentManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void USwordmasterEquipmentManagerComponent::Equip(int32 ItemId)
{
	if (FSwordmasterEquipmentRow* Row = SwordmasterDataTableHelper::BinarySearchBy<FSwordmasterEquipmentRow>(EquipmentsTable, ItemId, [](const FSwordmasterEquipmentRow* Row) { return Row->ItemId; }))
	{
		Equip(Row->EquipmentClass);
	}
}

void USwordmasterEquipmentManagerComponent::Equip(TSubclassOf<USwordmasterEquipmentInstance> InstanceClass)
{
	USwordmasterEquipmentInstance* NewInstance = NewObject<USwordmasterEquipmentInstance>(this, InstanceClass);
	USwordmasterEquipmentInstance* OldInstance = GetEquipmentInstance(NewInstance->GetSlotTag());

	Unequip(OldInstance);
	
	NewInstance->OnEquip();
	CurrentEquipmentInstances.Add(NewInstance->GetSlotTag(), NewInstance);

	FOnEquipmentChangeData ChangeData = { NewInstance->GetSlotTag(), NewInstance, OldInstance };
	OnEquipmentChanged.Broadcast(ChangeData);
}

void USwordmasterEquipmentManagerComponent::UnequipFromSlot(const FGameplayTag& SlotTag)
{
	if (!SlotTag.MatchesTag(SwordmasterGameplayTags::Equipment_Slot))
	{
		return;
	}

	if (USwordmasterEquipmentInstance* Instance = GetEquipmentInstance(SlotTag))
	{
		Unequip(Instance);

		FOnEquipmentChangeData ChangeData = { SlotTag, nullptr, Instance };
		OnEquipmentChanged.Broadcast(ChangeData);
	}
}

void USwordmasterEquipmentManagerComponent::UnequipFromId(int32 ItemId)
{
	USwordmasterEquipmentInstance* EquipmentInstance = nullptr;

	for (const TPair<FGameplayTag, TObjectPtr<USwordmasterEquipmentInstance>>& Elem : CurrentEquipmentInstances)
	{
		if (Elem.Value->GetItemId() == ItemId)
		{
			EquipmentInstance = Elem.Value;
			break;
		}
	}

	if (EquipmentInstance)
	{
		Unequip(EquipmentInstance);

		FOnEquipmentChangeData ChangeData = { EquipmentInstance->GetSlotTag(), nullptr, EquipmentInstance };
		OnEquipmentChanged.Broadcast(ChangeData);
	}
}

void USwordmasterEquipmentManagerComponent::Unequip(USwordmasterEquipmentInstance* Instance)
{
	if (Instance)
	{
		Instance->OnUnequip();
		CurrentEquipmentInstances.Remove(Instance->GetSlotTag());
	}
}

USwordmasterEquipmentInstance* USwordmasterEquipmentManagerComponent::GetEquipmentInstance(const FGameplayTag& SlotTag) const
{
	return CurrentEquipmentInstances.FindRef(SlotTag);
}

bool USwordmasterEquipmentManagerComponent::IsEquipped(int32 ItemId) const
{
	for (const TPair<FGameplayTag, TObjectPtr<USwordmasterEquipmentInstance>>& Elem : CurrentEquipmentInstances)
	{
		if (Elem.Value->GetItemId() == ItemId)
		{
			return true;
		}
	}

	return false;
}

void USwordmasterEquipmentManagerComponent::AddEquipmentActor(const FGameplayTag& SlotTag, AActor* EquipmentActor)
{
	CurrentEquipmentActors.Add(SlotTag, EquipmentActor);
	OnEquipmentActorAdded.Broadcast(EquipmentActor);
}

void USwordmasterEquipmentManagerComponent::RemoveEquipmentActor(const FGameplayTag& SlotTag)
{
	OnEquipmentActorRemoved.Broadcast(GetEquipmentActor(SlotTag));
	CurrentEquipmentActors.Remove(SlotTag);
}

AActor* USwordmasterEquipmentManagerComponent::GetEquipmentActor(const FGameplayTag& SlotTag) const
{
	return CurrentEquipmentActors.FindRef(SlotTag);
}
