#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/SwordmasterGameplayAbility.h"
#include "GenericTeamAgentInterface.h"
#include "SwordmasterGameplayAbility_MeleeAttack.generated.h"

class USwordmasterCombatComponent;

UCLASS()
class SWORDMASTER_API USwordmasterGameplayAbility_MeleeAttack : public USwordmasterGameplayAbility
{
	GENERATED_BODY()
	
public:
	//virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	//virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UFUNCTION(BlueprintPure, Category="Swordmaster|Ability")
	USwordmasterCombatComponent* GetCombatComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category="Swordmaster|Ability")
	bool HandleDamage(AActor* TargetActor, float Force) const;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> ImpactEffectClass;
};
