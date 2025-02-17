#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_RotateToFacingTarget.generated.h"

struct FRotateToFacingTargetTaskMemory
{
	TWeakObjectPtr<APawn> OwningPawn;
	TWeakObjectPtr<AActor> TargetActor;

	void Reset();
	bool IsValid() const;
};

UCLASS()
class SWORDMASTER_API UBTTask_RotateToFacingTarget : public UBTTaskNode
{
	GENERATED_BODY()
	
private:
	UBTTask_RotateToFacingTarget();

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual uint16 GetInstanceMemorySize() const override;
	virtual FString GetStaticDescription() const override;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	float GetAngleBetween(AActor* From, AActor* To) const;

private:
	UPROPERTY(EditAnywhere, Category="Facing Target")
	float AnglePrecision;

	UPROPERTY(EditAnywhere, Category="Facing Target")
	float RotationInterpSpeed;

	UPROPERTY(EditAnywhere, Category="Facing Target")
	FBlackboardKeySelector TargetActorKey;
};
