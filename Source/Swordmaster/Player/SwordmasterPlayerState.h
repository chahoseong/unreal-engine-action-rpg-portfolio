#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "SwordmasterPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class USwordmasterInventoryManagerComponent;

UCLASS()
class SWORDMASTER_API ASwordmasterPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	ASwordmasterPlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	template <typename T>
	T* GetAbilitySystemComponent() const
	{
		return Cast<T>(GetAbilitySystemComponent());
	}

	UAttributeSet* GetAttributeSet() const;

	template <typename T>
	T* GetAttributeSet() const
	{
		return Cast<T>(GetAttributeSet());
	}

	int32 GetLevel() const;

	UFUNCTION(BlueprintCallable)
	USwordmasterInventoryManagerComponent* GetInventory() const;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(VisibleAnywhere)
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USwordmasterInventoryManagerComponent> InventoryManager;
};
