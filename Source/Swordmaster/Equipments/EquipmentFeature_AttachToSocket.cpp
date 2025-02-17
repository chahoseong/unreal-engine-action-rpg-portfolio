#include "Equipments/EquipmentFeature_AttachToSocket.h"
#include "Equipments/SwordmasterEquipmentInstance.h"
#include "GameFramework/Character.h"

void UEquipmentFeature_AttachToSocket::OnInstanceEquipped(USwordmasterEquipmentInstance* Instance)
{
	APawn* OwningPawn = Cast<APawn>(Instance->GetOuter());
	if (!OwningPawn)
	{
		if (UActorComponent* ActorComp = Cast<UActorComponent>(Instance->GetOuter()))
		{
			OwningPawn = ActorComp->GetOwner<APawn>();
		}
	}

	USceneComponent* TargetToAttach = OwningPawn->GetRootComponent();

	if (ACharacter* OwningCharacter = Cast<ACharacter>(OwningPawn))
	{
		TargetToAttach = OwningCharacter->GetMesh();
	}

	SpawnedActor = GetWorld()->SpawnActor(ActorToSpawn);
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	SpawnedActor->AttachToComponent(TargetToAttach, AttachmentRules, AttachmentSocketName);
}

void UEquipmentFeature_AttachToSocket::OnInstanceUnequipped(USwordmasterEquipmentInstance* Instance)
{
	if (SpawnedActor)
	{
		SpawnedActor->Destroy();
		SpawnedActor = nullptr;
	}
}
