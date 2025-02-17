// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "SwordmasterComboSystemComponent.generated.h"

USTRUCT(BlueprintType)
struct FComboState
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int32 ComboIndex;

	UPROPERTY(BlueprintReadWrite)
	FGameplayTag AttackTag;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SWORDMASTER_API USwordmasterComboSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="Swordmaster|Component")
	static USwordmasterComboSystemComponent* FindComboSystemComponent(AActor* Actor);

public:
	USwordmasterComboSystemComponent();

	UFUNCTION(BlueprintCallable)
	void StartCombo(const FGameplayTag& AttackTag);

	UFUNCTION(BlueprintCallable)
	void AdvanceCombo(const FGameplayTag& AttackTag);

	UFUNCTION(BlueprintCallable)
	void ChangeCombo(const FGameplayTag& AttackTag, int32 ComboIndex);

	UFUNCTION(BlueprintPure)
	int32 GetLastComboIndex() const;

	UFUNCTION(BlueprintPure)
	const FGameplayTag& GetLastComboAttackTag() const;

	UFUNCTION(BlueprintCallable)
	void SetComboEnabled(bool bEnabled);

	UFUNCTION(BlueprintPure)
	bool IsComboEnabled() const;

protected:
	UPROPERTY(BlueprintReadOnly)
	FComboState LastComboState;

	UPROPERTY(BlueprintReadWrite)
	FGameplayTag SavedAttackTag;

private:
	bool bComboEnabled = false;
};
