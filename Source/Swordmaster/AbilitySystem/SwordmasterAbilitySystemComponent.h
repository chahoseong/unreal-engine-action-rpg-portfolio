#pragma once

#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpecHandle.h"
#include "SwordmasterAbilitySystemComponent.generated.h"

struct FGameplayTag;

UCLASS()
class SWORDMASTER_API USwordmasterAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	USwordmasterAbilitySystemComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	void AbilityInputTagPressed(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);

	void ProcessAbilityInput(float DeltaTime, bool bGamePaused);
	void ClearAbilityInput();

protected:
	TArray<FGameplayAbilitySpecHandle> InputPressedSpecHandles;
	TArray<FGameplayAbilitySpecHandle> InputReleasedSpecHandles;
	TArray<FGameplayAbilitySpecHandle> InputHeldSpecHandles;
};
