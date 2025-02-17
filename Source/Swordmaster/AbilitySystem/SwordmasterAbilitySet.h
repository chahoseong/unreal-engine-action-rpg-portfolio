#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameplayTagContainer.h"
#include "SwordmasterAbilitySet.generated.h"

class UGameplayAbility;
class UGameplayEffect;

USTRUCT(BlueprintType)
struct FSwordmasterAbilitySet_GameplayAbilityWithInputTag
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayAbility> Ability;

	UPROPERTY(EditDefaultsOnly, Meta = (Categories = "Input"))
	FGameplayTag InputTag;
};

USTRUCT(BlueprintType)
struct FSwordmasterAbilitySet_GrantedHandles
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
class SWORDMASTER_API USwordmasterAbilitySet : public UDataAsset
{
	GENERATED_BODY()
	
public:
	USwordmasterAbilitySet(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	FSwordmasterAbilitySet_GrantedHandles GiveToAbilitySystem(UAbilitySystemComponent* TargetAbilitySystem, UObject* SourceObject = nullptr) const;

public:
	UPROPERTY(EditDefaultsOnly, Meta=(TitleProperty="Ability"))
	TArray<TSubclassOf<UGameplayAbility>> GrantedGameplayAbilities;

	UPROPERTY(EditDefaultsOnly, Meta=(TitleProperty="Ability"))
	TArray<FSwordmasterAbilitySet_GameplayAbilityWithInputTag> GrantedGameplayAbilitiesWithInputTags;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayEffect>> GrantedGameplayEffects;
};
