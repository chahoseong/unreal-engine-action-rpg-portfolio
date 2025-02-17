#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_OnTick.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTickDelegate, float, DeltaTime);

UCLASS()
class SWORDMASTER_API UAbilityTask_OnTick : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category="Swordmaster|Ability Tasks", Meta=(HidePin="OwningAbility", DefaultToSelf="OwningAbility", BlueprintInternalUseOnly=True))
	static UAbilityTask_OnTick* OnTick(UGameplayAbility* OwningAbility);

	UPROPERTY(BlueprintAssignable)
	FOnTickDelegate OnSignal;

public:
	UAbilityTask_OnTick();

	virtual void TickTask(float DeltaTime) override;
};
