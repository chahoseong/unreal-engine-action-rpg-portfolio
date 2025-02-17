#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_OrientToTarget.generated.h"

UCLASS()
class SWORDMASTER_API UBTService_OrientToTarget : public UBTService
{
	GENERATED_BODY()
	
private:
	UBTService_OrientToTarget();

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual FString GetStaticDescription() const override;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, Category="Target")
	FBlackboardKeySelector TargetActorKey;

	UPROPERTY(EditAnywhere, Category="Target")
	float RotationInterpSpeed;
};
