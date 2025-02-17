#pragma once

#include "CoreMinimal.h"
#include "Characters/SwordmasterCharacter.h"
#include "Combat/SwordmasterCombatTarget.h"
#include "SwordmasterEnemyCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChanged, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnemyDead);

class UGameplayEffect;
class UWidgetComponent;
class USwordmasterCombatComponent;
class USwordmasterWeaponInstance;

UCLASS()
class SWORDMASTER_API ASwordmasterEnemyCharacter : public ASwordmasterCharacter, public ISwordmasterCombatTarget
{
	GENERATED_BODY()
	
public:
	ASwordmasterEnemyCharacter();

	virtual FGenericTeamId GetTeamId() const override;

	bool IsDead_Implementation() const override;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChanged OnMaxHealthChanged;

protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;

private:
	void LoadInitialAttributes();
	void OnInitialAttributesLoaded();

	void SetHealthBarWidgetController();

	void Die();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Swordmaster|Character")
	int32 EnemyId;

	UPROPERTY(EditDefaultsOnly, Category="Swordmaster|Character")
	TSoftObjectPtr<UDataTable> AttributesTable;

	UPROPERTY(EditDefaultsOnly, Category="Swordmaster|Character")
	TSubclassOf<UGameplayEffect> InitialAttributes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USwordmasterCombatComponent> CombatComponent;
};
