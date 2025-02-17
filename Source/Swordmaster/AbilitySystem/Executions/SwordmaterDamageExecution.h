#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "SwordmaterDamageExecution.generated.h"


UCLASS()
class SWORDMASTER_API USwordmaterDamageExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
public:
	USwordmaterDamageExecution();

protected:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
