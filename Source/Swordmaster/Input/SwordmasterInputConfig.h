#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "SwordmasterInputConfig.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FSwordmasterInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<const UInputAction> InputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta=(Categories="Input"))
	FGameplayTag InputTag;
};

UCLASS(BlueprintType, Const)
class SWORDMASTER_API USwordmasterInputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category="Swordmaster|Pawn")
	const UInputAction* FindNativeInputActionWithTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;

	UFUNCTION(BlueprintCallable, Category="Swordmaster|Pawn")
	const UInputAction* FindAbilityInputActionWithTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty=InputAction))
	TArray<FSwordmasterInputAction> NativeInputActions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty=InputAction))
	TArray<FSwordmasterInputAction> AbilityInputActions;
};
