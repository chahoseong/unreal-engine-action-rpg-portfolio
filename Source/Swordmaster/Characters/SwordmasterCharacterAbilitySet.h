#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SwordmasterCharacterAbilitySet.generated.h"

class UGameplayAbility;
class UGameplayEffect;
class UAbilitySystemComponent;

UCLASS()
class SWORDMASTER_API USwordmasterCharacterAbilitySet : public UDataAsset
{
	GENERATED_BODY()

public:
	USwordmasterCharacterAbilitySet(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	void GiveToAbilitySystem(UAbilitySystemComponent* TargetAbilitySystem, UObject* SourceObject = nullptr) const;

public:
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayAbility>> GrantedGameplayAbilities;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayEffect>> GrantedGameplayEffects;
};
