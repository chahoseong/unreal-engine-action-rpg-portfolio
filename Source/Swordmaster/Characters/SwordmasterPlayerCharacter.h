#pragma once

#include "CoreMinimal.h"
#include "Characters/SwordmasterCharacter.h"
#include "Combat/SwordmasterCombatComponent.h"
#include "Combat/SwordmasterCombatInterface.h"
#include "Combat/SwordmasterCombatTarget.h"
#include "GameplayTagContainer.h"
#include "SwordmasterPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USwordmasterCharacterPartsManagerComponent;
class USwordmasterEquipmentManagerComponent;
class USwordmasterEquipmentInstance;
struct FOnEquipmentChangeData;
class USwordmasterCombatComponent;
class USwordmasterComboSystemComponent;
class UMotionWarpingComponent;
class USwordmasterInteractorComponent;
class USceneCaptureComponent2D;

UCLASS()
class SWORDMASTER_API ASwordmasterPlayerCharacter : public ASwordmasterCharacter, public ISwordmasterCombatInterface, public ISwordmasterCombatTarget
{
	GENERATED_BODY()
	
public:
	ASwordmasterPlayerCharacter();

	virtual void PossessedBy(AController* NewController) override;

	virtual void Tick(float DeltaSeconds) override;

	USpringArmComponent* GetSpringArm() const;
	virtual USwordmasterCombatComponent* GetSwordmasterCombatComponent() const override;

	virtual FGenericTeamId GetTeamId() const override;

protected:
	virtual void BeginPlay() override;

private:
	virtual void InitAbilityActorInfo() override;
	void LoadCharacterParts();
	void InitAttributes();

	void OnCharacterPartsLoaded();
	void OnEquipmentChanged(const FOnEquipmentChangeData& Data);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(EditDefaultsOnly, Category="Swordmaster|Character")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(EditDefaultsOnly, Category="Swordmaster|Character")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	UPROPERTY(EditDefaultsOnly, Category="Swordmaster|Character")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	UPROPERTY(EditDefaultsOnly, Category="Swordmaster|Character")
	TSubclassOf<UGameplayEffect> DefaultCombatAttributes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USwordmasterCharacterPartsManagerComponent> CharacterPartsManager;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Swordmaster|Character", Meta=(RowType="SwordmasterCharacterPartRow"))
	TSoftObjectPtr<UDataTable> CharacterPartsDataTable;

	UPROPERTY(EditDefaultsOnly, Category="Swordmaster|Character")
	TArray<int32> InitialCharacterParts;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USwordmasterEquipmentManagerComponent> EquipmentManager;

	UPROPERTY(EditDefaultsOnly, Category="Swordmaster|Character")
	TSubclassOf<USwordmasterEquipmentInstance> DefaultWeaponInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USwordmasterCombatComponent> CombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USwordmasterComboSystemComponent> ComboSystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UMotionWarpingComponent> MotionWarpingComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USwordmasterInteractorComponent> InteractorComponent;
};
