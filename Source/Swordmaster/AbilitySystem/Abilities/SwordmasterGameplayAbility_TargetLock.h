#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/SwordmasterGameplayAbility.h"
#include "SwordmasterGameplayAbility_TargetLock.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTargetLockDelegate);

class USwordmasterUserWidget;
class UInputMappingContext;

UCLASS()
class SWORDMASTER_API USwordmasterGameplayAbility_TargetLock : public USwordmasterGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnTargetLockDelegate OnTargetLocked;
	
	UPROPERTY(BlueprintAssignable)
	FOnTargetLockDelegate OnTick;

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UFUNCTION(BlueprintCallable)
	void UpdateTargetLock(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	void SwitchTarget(const FGameplayTag& DirectionTag);

private:
	void CancelTargetLockAbility();

	void TryLockOnTarget();
	void FindAvailableActorsToLock();
	AActor* GetNearestTargetFromActors(const TArray<AActor*>& Actors);
	void DivideAvailableActorsOnDirection(TArray<AActor*>& ActorsOnLeft, TArray<AActor*>& ActorsOnRight);

	FVector GetControlForwardVector() const;

	void InitInputMapping();
	void ResetInputMapping();

	void ShowIndicatorWidget();
	void HideIndicatorWidget();

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AActor> CurrentLockedActor;

	UPROPERTY(EditDefaultsOnly, Category="Target Lock")
	float TraceMaxDistance = 5000.0f;

	UPROPERTY(EditDefaultsOnly, Category="Target Lock")
	FVector TraceBoxSize = FVector(5000.0f, 5000.0f, 300.0f);

	UPROPERTY(EditDefaultsOnly, Category="Target Lock")
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceQueryChannel;

	UPROPERTY(EditDefaultsOnly, Category="Target Lock")
	bool bShowTraceDebug = false;

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	float ViewPitchOffset = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category="Target Lock")
	float RotationSpeed = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	TObjectPtr<UInputMappingContext> InputMapping;

	UPROPERTY(EditDefaultsOnly, Category="Target Lock")
	TSubclassOf<USwordmasterUserWidget> IndicatorWidgetClass;

private:
	UPROPERTY()
	TArray<TObjectPtr<AActor>> AvailableActorsToLock;

	UPROPERTY()
	TObjectPtr<USwordmasterUserWidget> ActiveIndicatorWidget;

	bool bCachedOrientRotationToMovement;

	bool bShouldActorRotateTowardsTarget = false;
};
