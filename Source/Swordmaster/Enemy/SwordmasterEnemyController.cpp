#include "Enemy/SwordmasterEnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Combat/SwordmasterCombatTarget.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "SwordmasterFunctionLibrary.h"

ASwordmasterEnemyController::ASwordmasterEnemyController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))
{
	SenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SenseConfig_Sight"));
	SenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
	SenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;
	SenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false;
	SenseConfig_Sight->SightRadius = 5000.f;
	SenseConfig_Sight->LoseSightRadius = 0.0f;
	SenseConfig_Sight->PeripheralVisionAngleDegrees = 360.0f;

	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
	PerceptionComponent->ConfigureSense(*SenseConfig_Sight);
	PerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
	PerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ThisClass::OnEnemyPerceptionUpdated);

	SetGenericTeamId(FGenericTeamId(1));
}

ETeamAttitude::Type ASwordmasterEnemyController::GetTeamAttitudeTowards(const AActor& Other) const
{
	if (const APawn* OtherPawn = Cast<APawn>(&Other))
	{
		if (const IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()))
		{
			if (TeamAgent->GetGenericTeamId() < GetGenericTeamId())
			{
				return ETeamAttitude::Hostile;
			}
			else
			{
				return ETeamAttitude::Friendly;
			}
		}
	}

	return ETeamAttitude::Neutral;
}

void ASwordmasterEnemyController::BeginPlay()
{
	Super::BeginPlay();

	if (UCrowdFollowingComponent* CrowdFollowing = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		CrowdFollowing->SetCrowdSimulationState(bEnableDetourCrowdAvoidance ? ECrowdSimulationState::Enabled : ECrowdSimulationState::Disabled);
		
		switch (DetourCrowdAvoidanceQuality)
		{
		case 1:
			CrowdFollowing->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Low);
			break;
		case 2:
			CrowdFollowing->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Medium);
			break;
		case 3:
			CrowdFollowing->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Good);
			break;
		case 4:
			CrowdFollowing->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);
			break;
		}

		CrowdFollowing->SetAvoidanceGroup(1);
		CrowdFollowing->SetGroupsToAvoid(1);
		CrowdFollowing->SetCrowdCollisionQueryRange(CollisionQueryRange);
	}
}

void ASwordmasterEnemyController::OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed() && Actor)
	{
		if (Blackboard && !Blackboard->GetValueAsObject(FName("TargetActor")))
		{
			Blackboard->SetValueAsObject(FName("TargetActor"), Actor);
		}
	}
}
