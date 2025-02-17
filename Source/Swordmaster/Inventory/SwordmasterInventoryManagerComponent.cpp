#include "Inventory/SwordmasterInventoryManagerComponent.h"
#include "SwordmasterDataTableHelper.h"

const int32 InventoryEmptyItem = -1;

/*
 * FInventoryEntry
 */

void FInventoryEntry::InitSlots()
{
	Slots.SetNum(Capacity, false);
}

bool FInventoryEntry::AddItem(int32 ItemId, int32 Quantity)
{
	if (Count + 1 < Capacity)
	{
		Slots[Count].ItemId = ItemId;
		Slots[Count].Quantity = Quantity;
		++Count;
		return true;
	}

	return false;
}

bool FInventoryEntry::RemoveItem(int32 ItemId, int32 Quantity)
{
	bool bShouldRemoveSlot = false;
	int32 Cursor = 0;

	for (int32 Index = 0; Index < Count; ++Index)
	{
		if (Slots[Index].ItemId == ItemId)
		{
			if (Slots[Index].Quantity < Quantity)
			{
				return false;
			}
			Slots[Index].Quantity -= Quantity;
			bShouldRemoveSlot = (Slots[Index].Quantity == 0);
			Cursor = Index;
			break;
		}
	}

	if (bShouldRemoveSlot)
	{
		for (int32 i = Cursor; i < Count - 1; ++i)
		{
			Slots[i].ItemId = Slots[i + 1].ItemId;
			Slots[i].Quantity = Slots[i + 1].Quantity;
		}
		Slots[Count - 1].ItemId = InventoryEmptyItem;
		Slots[Count - 1].Quantity = 0;
		--Count;
	}

	return true;
}

bool FInventoryEntry::HasItem(int32 ItemId) const
{
	return ToIndex(ItemId) != INDEX_NONE;
}

FInventorySlot* FInventoryEntry::FindSlot(int32 ItemId) 
{
	for (int32 Index = 0; Index < Count; ++Index)
	{
		if (Slots[Index].ItemId == ItemId)
		{
			return &Slots[Index];
		}
	}

	return nullptr;
}

int32 FInventoryEntry::ToIndex(int32 ItemId) const
{
	for (int32 i = 0; i < Count; ++i)
	{
		if (Slots[i].ItemId == ItemId)
		{
			return i;
		}
	}

	return INDEX_NONE;
}

/*
 * USwordmasterInventoryManagerComponent
 */

USwordmasterInventoryManagerComponent::USwordmasterInventoryManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USwordmasterInventoryManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// TODO: 저장된 데이터 불러오기
	for (TPair<ESwordmasterItemCategory, FInventoryEntry>& Elem : Entries)
	{
		Elem.Value.InitSlots();
	}
}

bool USwordmasterInventoryManagerComponent::AddItem(int32 ItemId, int32 Quantity)
{
	FSwordmasterItemDefinition* Found = SwordmasterDataTableHelper::BinarySearchBy<FSwordmasterItemDefinition>(ItemTable, ItemId, [](const FSwordmasterItemDefinition* Item) { return Item->ItemId; });
	check(Found);

	FInventoryEntry* Entry = Entries.Find(Found->Category);
	FInventorySlot* Slot = Entry->FindSlot(ItemId);

	// Create Slot
	if (!Slot)
	{
		return Entry->AddItem(ItemId, Quantity);
	}

	// Update Slot
	if (Slot->Quantity + Quantity <= Found->MaxQuantity)
	{
		Slot->Quantity += Quantity;
		return true;
	}

	return false;
}

bool USwordmasterInventoryManagerComponent::RemoveItem(int32 ItemId, int32 Quantity)
{
	FSwordmasterItemDefinition* Found = SwordmasterDataTableHelper::BinarySearchBy<FSwordmasterItemDefinition>(ItemTable, ItemId, [](const FSwordmasterItemDefinition* Item) { return Item->ItemId; });
	check(Found);
	FInventoryEntry* Entry = Entries.Find(Found->Category);
	return Entry->RemoveItem(ItemId, Quantity);
}
