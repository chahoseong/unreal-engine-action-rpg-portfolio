#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "GameplayTagContainer.h"
#include "SwordmasterCombatTarget.h"
#include "GenericTeamAgentInterface.h"
#include "SwordmasterCombatComponent.generated.h"

class ISwordmasterCombatWeapon;
class UAnimMontage;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttackHit, const TArray<AActor*>&, TargetsOnHit);

USTRUCT(BlueprintType)
struct FHitReactMontages
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Swordmaster|Combat")
	TObjectPtr<UAnimMontage> Forward;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Swordmaster|Combat")
	TObjectPtr<UAnimMontage> Backward;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Swordmaster|Combat")
	TObjectPtr<UAnimMontage> Left;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Swordmaster|Combat")
	TObjectPtr<UAnimMontage> Right;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SWORDMASTER_API USwordmasterCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="Swordmater|Component")
	static USwordmasterCombatComponent* FindCombatComponent(AActor* Actor);

public:	
	USwordmasterCombatComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetWeapon(TScriptInterface<ISwordmasterCombatWeapon> NewWeapon);

	UFUNCTION(BlueprintCallable)
	void SetWeaponDamageEnabled(bool bEnabled);

	UFUNCTION(BlueprintCallable)
	void DrawDebugHitBox();

	UPROPERTY(BlueprintAssignable)
	FOnAttackHit OnAttackHit;

private:
	bool IsDead(AActor* Actor) const;
	bool IsAttackParried(AActor* Actor) const;
	bool IsAttackBlocked(AActor* Actor, float& Cost) const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Swordmaster|Combat")
	TScriptInterface<ISwordmasterCombatWeapon> CurrentWeapon;

	UPROPERTY(EditAnywhere, Category="Swordmaster|Combat")
	FVector HitBoxOffset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Swordmaster|Combat")
	float KnockdownThreshold;

	UPROPERTY(EditDefaultsOnly, Category="Swordmaster|Combat")
	float DefensibleMaxAngle = 45.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Swordmaster|Combat")
	FHitReactMontages HitReactMontages;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Swordmaster|Combat")
	TObjectPtr<UAnimMontage> KnockdownMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Swordmaster|Combat")
	TObjectPtr<UAnimMontage> WakeupMontage;

private:
	bool bWeaponDamageEnabled = false;
	FVector HitBoxLocation;
	FCollisionQueryParams HitBoxQueryParams;
};
