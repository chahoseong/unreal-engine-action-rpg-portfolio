#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SwordmasterAnimInstance.generated.h"

UENUM(BlueprintType)
enum class ELocomotionDirection : uint8
{
	Forward,
	Backward,
	Left,
	Right,
};

UCLASS()
class SWORDMASTER_API USwordmasterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	USwordmasterAnimInstance(const FObjectInitializer& ObjectInitializer);

protected:
	UFUNCTION(BlueprintPure, Meta=(BlueprintThreadSafe))
	ELocomotionDirection CalculateLocomotionDirection(float Angle, float DeadZone, ELocomotionDirection CurrentDirection, bool bUseCurrentDirection) const;
};
