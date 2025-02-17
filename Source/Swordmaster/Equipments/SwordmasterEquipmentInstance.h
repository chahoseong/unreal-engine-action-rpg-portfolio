#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "ActiveGameplayEffectHandle.h"
#include "SwordmasterEquipmentInstance.generated.h"

class USwordmasterEquipmentFeature;
class UGameplayEffect;

UCLASS(Blueprintable, BlueprintType)
class SWORDMASTER_API USwordmasterEquipmentInstance : public UObject
{
	GENERATED_BODY()
	
public:
	int32 GetItemId() const;
	const FGameplayTag& GetSlotTag() const;

	virtual void OnEquip();
	virtual void OnUnequip();

private:
	UAbilitySystemComponent* GetAbilitySystemComponent() const;


protected:
	UPROPERTY(EditDefaultsOnly, Category="Equipment")
	int32 ItemId;

	UPROPERTY(EditDefaultsOnly, Category="Equipment", Meta=(Categories="Equipment.Slot"))
	FGameplayTag SlotTag;

	UPROPERTY(EditDefaultsOnly, Category="Equipment", Instanced)
	TArray<TObjectPtr<USwordmasterEquipmentFeature>> EquipmentFeatures;

	UPROPERTY(EditDefaultsOnly, Category="Equipment")
	TArray<TSubclassOf<UGameplayEffect>> GameplayEffectsToGrant;

	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
	TObjectPtr<UDataTable> AttributesTable;

private:
	TArray<FActiveGameplayEffectHandle> ActiveGameplayEffects;
};
