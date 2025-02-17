#include "AI/Services/BTService_OrientToTarget.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

UBTService_OrientToTarget::UBTService_OrientToTarget()
{
	NodeName = TEXT("Orient Rotation To Target");
	INIT_SERVICE_NODE_NOTIFY_FLAGS();

	RotationInterpSpeed = 5.0f;
	Interval = 0.0f;
	RandomDeviation = 0.0f;

	TargetActorKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(ThisClass, TargetActorKey), AActor::StaticClass());
}

void UBTService_OrientToTarget::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	if (UBlackboardData* BlackboardAsset = GetBlackboardAsset())
	{
		TargetActorKey.ResolveSelectedKey(*BlackboardAsset);
	}
}

FString UBTService_OrientToTarget::GetStaticDescription() const
{
	const FString KeyDescription = TargetActorKey.SelectedKeyName.ToString();
	return FString::Printf(TEXT("Orient rotation to %s Key %s"), *KeyDescription, *GetStaticServiceDescription());
}

void UBTService_OrientToTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UObject* TargetObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetActorKey.SelectedKeyName);
	AActor* TargetActor = Cast<AActor>(TargetObject);

	APawn* OwningPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (OwningPawn && TargetActor)
	{
		const FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(OwningPawn->GetActorLocation(), TargetActor->GetActorLocation());
		const FRotator RotationStep = FMath::RInterpTo(OwningPawn->GetActorRotation(), LookAtRotation, DeltaSeconds, RotationInterpSpeed);
		OwningPawn->SetActorRotation(RotationStep);
	}
}
