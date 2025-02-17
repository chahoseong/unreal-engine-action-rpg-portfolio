#include "AbilitySystem/Tasks/AbilityTask_RotateToMovement.h"

UAbilityTask_RotateToMovement* UAbilityTask_RotateToMovement::RotateToMovement(UGameplayAbility* OwningAbility, FName TaskInstanceName)
{
	UAbilityTask_RotateToMovement* Task = NewAbilityTask<UAbilityTask_RotateToMovement>(OwningAbility, TaskInstanceName);
	return Task;
}

UAbilityTask_RotateToMovement::UAbilityTask_RotateToMovement(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bTickingTask = true;
}

void UAbilityTask_RotateToMovement::Activate()
{
	State = EState::Started;
}

void UAbilityTask_RotateToMovement::TickTask(float DeltaTime)
{
	if (State == EState::Finished)
	{
		return;
	}

	Super::TickTask(DeltaTime);

	if (AActor* AvatarActor = GetAvatarActor())
	{
		FRotator CurrentRotation = AvatarActor->GetActorRotation();

		switch (State)
		{
		case EState::Started:
			LastRotation = CurrentRotation;
			State = EState::Updating;
			break;
		case EState::Updating:
			if (CurrentRotation.EqualsOrientation(LastRotation))
			{
				State = EState::Finished;
				OnComplete.Broadcast();
				EndTask();
			}
			else
			{
				LastRotation = CurrentRotation;
			}
			break;
		}
	}
	else
	{
		State = EState::Finished;
		EndTask();
	}
}
