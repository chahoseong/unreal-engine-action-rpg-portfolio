#include "AI/Tasks/BTTask_RotateToFacingTarget.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

/*
 * FRotateToFacingTargetTaskMemory
 */

void FRotateToFacingTargetTaskMemory::Reset()
{
	OwningPawn.Reset();
	TargetActor.Reset();
}

bool FRotateToFacingTargetTaskMemory::IsValid() const
{
	return OwningPawn.IsValid() && TargetActor.IsValid();
}

/*
 * UBTTask_RotateToFacingTarget
 */

UBTTask_RotateToFacingTarget::UBTTask_RotateToFacingTarget()
{
	NodeName = TEXT("Rotate to Facing Target");
	AnglePrecision = 10.0f;
	RotationInterpSpeed = 5.0f;

	bNotifyTick = true;
	bNotifyTaskFinished = true;
	bCreateNodeInstance = false;

	INIT_TASK_NODE_NOTIFY_FLAGS();

	TargetActorKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(ThisClass, TargetActorKey), AActor::StaticClass());
}

void UBTTask_RotateToFacingTarget::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	if (UBlackboardData* BBAsset = GetBlackboardAsset())
	{
		TargetActorKey.ResolveSelectedKey(*BBAsset);
	}
}

uint16 UBTTask_RotateToFacingTarget::GetInstanceMemorySize() const
{
	return sizeof(FRotateToFacingTargetTaskMemory);
}

FString UBTTask_RotateToFacingTarget::GetStaticDescription() const
{
	const FString KeyDescription = TargetActorKey.SelectedKeyName.ToString();
	return FString::Printf(TEXT("Smoothly rotates to face %s Key until the angle precision %s is reached."),
		*KeyDescription,
		*FString::SanitizeFloat(AnglePrecision));
}

EBTNodeResult::Type UBTTask_RotateToFacingTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UObject* TargetObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetActorKey.SelectedKeyName);
	AActor* TargetActor = Cast<AActor>(TargetObject);

	APawn* OwningPawn = OwnerComp.GetAIOwner()->GetPawn();
	FRotateToFacingTargetTaskMemory* Memory = CastInstanceNodeMemory<FRotateToFacingTargetTaskMemory>(NodeMemory);

	check(Memory);

	Memory->OwningPawn = OwningPawn;
	Memory->TargetActor = TargetActor;

	if (!Memory->IsValid())
	{
		return EBTNodeResult::Failed;
	}

	if (GetAngleBetween(OwningPawn, TargetActor) <= AnglePrecision)
	{
		Memory->Reset();
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::InProgress;
}

void UBTTask_RotateToFacingTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FRotateToFacingTargetTaskMemory* Memory = CastInstanceNodeMemory<FRotateToFacingTargetTaskMemory>(NodeMemory);

	if (!Memory->IsValid())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	if (GetAngleBetween(Memory->OwningPawn.Get(), Memory->TargetActor.Get()) <= AnglePrecision)
	{
		Memory->Reset();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else
	{
		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(
			Memory->OwningPawn->GetActorLocation(),
			Memory->TargetActor->GetActorLocation()
		);
		FRotator RotationStep = FMath::RInterpTo(Memory->OwningPawn->GetActorRotation(), TargetRotation, DeltaSeconds, RotationInterpSpeed);
		Memory->OwningPawn->SetActorRotation(RotationStep);
	}
}

float UBTTask_RotateToFacingTarget::GetAngleBetween(AActor* From, AActor* To) const
{
	const FVector Forward = From->GetActorForwardVector();
	const FVector ToDirection = (To->GetActorLocation() - From->GetActorLocation()).GetSafeNormal();

	const float DotResult = FVector::DotProduct(Forward, ToDirection);
	
	return UKismetMathLibrary::DegAcos(DotResult);
}
