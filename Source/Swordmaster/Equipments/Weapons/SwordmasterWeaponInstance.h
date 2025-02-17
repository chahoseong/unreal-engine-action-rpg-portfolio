#pragma once

#include "CoreMinimal.h"
#include "Equipments/SwordmasterEquipmentInstance.h"
#include "AbilitySystem/SwordmasterAbilitySet.h"
#include "Combat/SwordmasterCombatWeapon.h"
#include "SwordmasterWeaponInstance.generated.h"

struct FGameplayAbilitySpecHandle;
class USwordmasterWeaponFeature;
class UNiagaraComponent;

UCLASS()
class SWORDMASTER_API USwordmasterWeaponInstance : public USwordmasterEquipmentInstance, public ISwordmasterCombatWeapon
{
	GENERATED_BODY()
	
public:
	virtual void OnEquip() override;
	virtual void OnUnequip() override;

	FVector GetAttackBoundary_Implementation() const override;

	void SpawnTrailEffect_Implementation(UNiagaraSystem* SystemTemplate, FName AttachPointName) override;
	void DestroyTrailEffect_Implementation() override;

	FVector GetSocketLocation_Implementation(FName SocketName) const override;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TSubclassOf<UAnimInstance> AnimLayerClass;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TObjectPtr<USwordmasterAbilitySet> AbilitySet;

	UPROPERTY(EditDefaultsOnly, Category="Weapon", Instanced)
	TArray<TObjectPtr<USwordmasterWeaponFeature>> WeaponFeatures;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	FVector AttackBoundary;

private:
	FSwordmasterAbilitySet_GrantedHandles GrantedHandles;
};
