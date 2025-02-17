#include "Equipments/EquipmentFeature_AttachToEquipmentManager.h"
#include "Equipments/SwordmasterEquipmentManagerComponent.h"
#include "Equipments/SwordmasterEquipmentInstance.h"
#include "GameFramework/Character.h"

void UEquipmentFeature_AttachToEquipmentManager::OnInstanceEquipped(USwordmasterEquipmentInstance* Instance)
{
	USwordmasterEquipmentManagerComponent* EquipmentManager = Cast<USwordmasterEquipmentManagerComponent>(Instance->GetOuter());
	check(EquipmentManager);
	
	if (APawn* OwningPawn = EquipmentManager->GetOwner<APawn>())
	{
		USceneComponent* TargetToAttach = OwningPawn->GetRootComponent();

		if (ACharacter* OwningCharacter = Cast<ACharacter>(OwningPawn))
		{
			TargetToAttach = OwningCharacter->GetMesh();
		}

		SpawnedActor = GetWorld()->SpawnActor(ActorToSpawn);
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, true);
		SpawnedActor->AttachToComponent(TargetToAttach, AttachmentRules, AttachmentSocketName);

		EquipmentManager->AddEquipmentActor(Instance->GetSlotTag(), SpawnedActor);
	}
}

void UEquipmentFeature_AttachToEquipmentManager::OnInstanceUnequipped(USwordmasterEquipmentInstance* Instance)
{
	USwordmasterEquipmentManagerComponent* EquipmentManager = Cast<USwordmasterEquipmentManagerComponent>(Instance->GetOuter());
	check(EquipmentManager);

	EquipmentManager->RemoveEquipmentActor(Instance->GetSlotTag());

	if (SpawnedActor)
	{
		SpawnedActor->Destroy();
	}
}
