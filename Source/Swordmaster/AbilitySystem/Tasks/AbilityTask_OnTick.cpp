#include "AbilitySystem/Tasks/AbilityTask_OnTick.h"

UAbilityTask_OnTick* UAbilityTask_OnTick::OnTick(UGameplayAbility* OwningAbility)
{
	UAbilityTask_OnTick* Task = NewAbilityTask<UAbilityTask_OnTick>(OwningAbility);
	return Task;
}

UAbilityTask_OnTick::UAbilityTask_OnTick()
{
	bTickingTask = true;
}

void UAbilityTask_OnTick::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnSignal.Broadcast(DeltaTime);
	}
	else
	{
		EndTask();
	}
}
