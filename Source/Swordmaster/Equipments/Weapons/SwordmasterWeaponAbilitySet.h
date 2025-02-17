#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameplayTagContainer.h"
#include "SwordmasterWeaponAbilitySet.generated.h"

class UGameplayAbility;
class UGameplayEffect;

USTRUCT(BlueprintType)
struct FSwordmasterWeaponAbilitySet_GameplayAbility
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayAbility> Ability;

	UPROPERTY(EditDefaultsOnly, Meta=(Categories="Input"))
	FGameplayTag InputTag;
};

USTRUCT(BlueprintType)
struct FSwordmasterWeaponAbilitySet_GrantedHandles
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

	UPROPERTY()
	TArray<FActiveGameplayEffectHandle> EffectSpecHandles;

	void AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle);
	void AddEffectSpecHandle(const FActiveGameplayEffectHandle& Handle);

	void Reset(UAbilitySystemComponent* AbilitySystem);
};

UCLASS()
class SWORDMASTER_API USwordmasterWeaponAbilitySet : public UDataAsset
{
	GENERATED_BODY()
	
public:
	USwordmasterWeaponAbilitySet(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	FSwordmasterWeaponAbilitySet_GrantedHandles GiveToAbilitySystem(UAbilitySystemComponent* TargetAbilitySystem, UObject* SourceObject = nullptr) const;

public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FSwordmasterWeaponAbilitySet_GameplayAbility> GrantedGameplayAbilities;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayEffect>> GrantedGameplayEffects;
};
