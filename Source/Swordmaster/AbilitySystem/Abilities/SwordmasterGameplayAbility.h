#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayTagContainer.h"
#include "SwordmasterGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class ESwordmasterAbilityActivationPolicy : uint8
{
	OnInputTriggered,
	WhileInputActive,
	OnGiven,
};

class ASwordmasterPlayerController;

UCLASS()
class SWORDMASTER_API USwordmasterGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	ESwordmasterAbilityActivationPolicy GetActivationPolicy() const;

	UFUNCTION(BlueprintCallable, Category="Swordmaster|Ability")
	AController* GetControllerFromActorInfo() const;

	template <typename T>
	T* GetControllerFromActorInfo() const
	{
		return Cast<T>(GetControllerFromActorInfo());
	}

	UFUNCTION(BlueprintCallable, Category="Swordmaster|Ability")
	void AddGameplayTagIfNotContainsFromActorInfo(const FGameplayTag& TagToAdd);

	UFUNCTION(BlueprintCallable, Category="Swordmaster|Ability")
	void AddGameplayTagFromActorInfo(const FGameplayTag& TagToAdd);

	UFUNCTION(BlueprintCallable, Category = "Swordmaster|Ability")
	void RemoveGameplayTagIfContainsFromActorInfo(const FGameplayTag& TagToRemove);

	UFUNCTION(BlueprintCallable, Category="Swordmaster|Ability")
	void RemoveGameplayTagFromActorInfo(const FGameplayTag& TagToRemove);

	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnInputPressed")
	void K2_OnInputPressed();

	UFUNCTION(BlueprintImplementableEvent, DisplayName = "OnInputReleased")
	void K2_OnInputReleased();

protected:
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Swordmaster|Ability Activation")
	ESwordmasterAbilityActivationPolicy ActivationPolicy;
};
