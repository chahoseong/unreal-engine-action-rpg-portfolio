#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "SwordmasterCharacter.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayAbility;
class UGameplayEffect;
class USwordmasterAbilitySet;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterDead);

UCLASS()
class SWORDMASTER_API ASwordmasterCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ASwordmasterCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;
	UAttributeSet* GetAttributeSet() const;

	UPROPERTY(BlueprintAssignable)
	FOnCharacterDead OnDead;

protected:
	virtual void InitAbilityActorInfo();
	void ApplyStartupAbilitySet();

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> EffectClass, float Level);

protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly, Category="Swordmaster|Character")
	TObjectPtr<USwordmasterAbilitySet> StartupAbilitySet;
};
