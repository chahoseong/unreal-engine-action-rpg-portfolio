#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item/SwordmasterItemDefinition.h"
#include "SwordmasterInventoryManagerComponent.generated.h"

extern const int32 InventoryEmptyItem;

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	int32 ItemId = InventoryEmptyItem;

	UPROPERTY(BlueprintReadOnly)
	int32 Quantity = 0;

	FInventorySlot() = default;
	FInventorySlot(int32 ItemId, int32 Quantity) : ItemId(ItemId), Quantity(Quantity) { }
};

USTRUCT(BlueprintType)
struct FInventoryEntry
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FInventorySlot> Slots;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Capacity;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Count;

	void InitSlots();

	bool AddItem(int32 ItemId, int32 Quantity);
	bool RemoveItem(int32 ItemId, int32 Quantity);
	bool HasItem(int32 ItemId) const;

	FInventorySlot* FindSlot(int32 ItemId);

	int32 ToIndex(int32 ItemId) const;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SWORDMASTER_API USwordmasterInventoryManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USwordmasterInventoryManagerComponent();

	UFUNCTION(BlueprintCallable)
	bool AddItem(int32 ItemId, int32 Quantity = 1);

	UFUNCTION(BlueprintCallable)
	bool RemoveItem(int32 ItemId, int32 Quantity = 1);

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Inventory")
	TObjectPtr<UDataTable> ItemTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory")
	TMap<ESwordmasterItemCategory, FInventoryEntry> Entries;
};
