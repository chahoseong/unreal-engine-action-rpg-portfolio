#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "SwordmasterEquipmentManagerComponent.generated.h"

class USwordmasterEquipmentSet;
class USwordmasterEquipmentInstance;

struct FOnEquipmentChangeData
{
	FGameplayTag SlotTag;
	USwordmasterEquipmentInstance* NewEquipment;
	USwordmasterEquipmentInstance* OldEquipment;
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnEquipmentChanged, const FOnEquipmentChangeData&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquipmentActorDelegate, AActor*, EquipmentActor);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SWORDMASTER_API USwordmasterEquipmentManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USwordmasterEquipmentManagerComponent();

	UFUNCTION(BlueprintCallable)
	void Equip(int32 ItemId);

	void Equip(TSubclassOf<USwordmasterEquipmentInstance> InstanceClass);

	UFUNCTION(BlueprintCallable)
	void UnequipFromSlot(const FGameplayTag& SlotTag);

	UFUNCTION(BlueprintCallable)
	void UnequipFromId(int32 ItemId);

	void Unequip(USwordmasterEquipmentInstance* Instance);

	USwordmasterEquipmentInstance* GetEquipmentInstance(const FGameplayTag& SlotTag) const;

	template <typename T>
	T* GetEquipmentInstance(const FGameplayTag& SlotTag)
	{
		return Cast<T>(GetEquipmentInstance(SlotTag));
	}

	UFUNCTION(BlueprintCallable)
	bool IsEquipped(int32 ItemId) const;

	void AddEquipmentActor(const FGameplayTag& SlotTag, AActor* EquipmentActor);
	void RemoveEquipmentActor(const FGameplayTag& SlotTag);
	AActor* GetEquipmentActor(const FGameplayTag& SlotTag) const;

	FOnEquipmentChanged OnEquipmentChanged;

	UPROPERTY(BlueprintAssignable)
	FOnEquipmentActorDelegate OnEquipmentActorAdded;

	UPROPERTY(BlueprintAssignable)
	FOnEquipmentActorDelegate OnEquipmentActorRemoved;

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Swordmaster|Equipment")
	TObjectPtr<UDataTable> EquipmentsTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Swordmaster|Equipment")
	TMap<FGameplayTag, TObjectPtr<USwordmasterEquipmentInstance>> CurrentEquipmentInstances;

private:
	UPROPERTY()
	TMap<FGameplayTag, TObjectPtr<AActor>> CurrentEquipmentActors;
};
