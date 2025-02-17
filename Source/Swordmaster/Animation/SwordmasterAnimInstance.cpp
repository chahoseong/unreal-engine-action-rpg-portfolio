// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/SwordmasterAnimInstance.h"
#include "SwordmasterAnimInstance.h"

USwordmasterAnimInstance::USwordmasterAnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

ELocomotionDirection USwordmasterAnimInstance::CalculateLocomotionDirection(float Angle, float DeadZone, ELocomotionDirection CurrentDirection, bool bUseCurrentDirection) const
{
	float ForwardDeadZone = DeadZone;
	float BackwardDeadZone = DeadZone;

	if (bUseCurrentDirection)
	{
		switch (CurrentDirection)
		{
		case ELocomotionDirection::Forward:
			ForwardDeadZone *= 2.0f;
			break;
		case ELocomotionDirection::Backward:
			BackwardDeadZone *= 2.0f;
			break;
		}
	}

	float AngleAbs = FMath::Abs(Angle);

	if (AngleAbs <= ForwardDeadZone + 45.0f)
	{
		return ELocomotionDirection::Forward;
	}
	else if (AngleAbs >= 135.0f - BackwardDeadZone)
	{
		return ELocomotionDirection::Backward;
	}
	else if (Angle > 0)
	{
		return ELocomotionDirection::Right;
	}
	else
	{
		return ELocomotionDirection::Left;
	}
}
