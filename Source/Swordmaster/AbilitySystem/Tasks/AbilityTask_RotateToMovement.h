#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_RotateToMovement.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRotateToMovementEvent);

UCLASS()
class SWORDMASTER_API UAbilityTask_RotateToMovement : public UAbilityTask
{
	GENERATED_BODY()

private:
	enum class EState
	{
		Started,
		Updating,
		Finished,
	};

public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UAbilityTask_RotateToMovement* RotateToMovement(UGameplayAbility* OwningAbility, FName TaskInstanceName);

public:
	UAbilityTask_RotateToMovement(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable)
	FRotateToMovementEvent OnComplete;

protected:
	EState State;
	FRotator LastRotation;	
	bool bFinished = false;
};
