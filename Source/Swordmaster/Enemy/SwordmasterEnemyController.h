#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "SwordmasterEnemyController.generated.h"

class UAISenseConfig_Sight;

UCLASS()
class SWORDMASTER_API ASwordmasterEnemyController : public AAIController
{
	GENERATED_BODY()
	
public:
	ASwordmasterEnemyController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	virtual void OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAISenseConfig_Sight> SenseConfig_Sight;

	UPROPERTY(EditDefaultsOnly, Category="Detour Crowd Avoidance Config")
	bool bEnableDetourCrowdAvoidance = true;

	UPROPERTY(EditDefaultsOnly, Category="Detour Crowd Avoidance Config", meta=(EditCondition="bEnableDetourCrowdAvoidance", UIMin="1", UIMax="4"))
	int32 DetourCrowdAvoidanceQuality = 4;

	UPROPERTY(EditDefaultsOnly, Category="Detour Crowd Avoidance Config", meta=(EditCondition="bEnableDetourCrowdAvoidance"))
	float CollisionQueryRange = 600.0f;
};
