#include "Equipments/Weapons/SwordmasterWeaponInstance.h"
#include "Equipments/Weapons/SwordmasterWeaponAbilitySet.h"
#include "Equipments/Weapons/SwordmasterWeaponFeature.h"
#include "Equipments/SwordmasterEquipmentManagerComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/SwordmasterAbilitySystemComponent.h"
#include "GameplayAbilitySpecHandle.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "SwordmasterGameplayTags.h"

void USwordmasterWeaponInstance::OnEquip()
{
	Super::OnEquip();

	USwordmasterEquipmentManagerComponent* Manager = Cast<USwordmasterEquipmentManagerComponent>(GetOuter());
	AActor* Owner = Manager->GetOwner();

	// Link anim layer
	USkeletalMeshComponent* Mesh = Owner->GetComponentByClass<USkeletalMeshComponent>();
	Mesh->LinkAnimClassLayers(AnimLayerClass);

	// Grant abilities
	if (IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(Owner))
	{
		USwordmasterAbilitySystemComponent* AbilitySystem = Cast<USwordmasterAbilitySystemComponent>(AbilitySystemInterface->GetAbilitySystemComponent());
		GrantedHandles = AbilitySet->GiveToAbilitySystem(AbilitySystem);
	}

	for (USwordmasterWeaponFeature* Feature : WeaponFeatures)
	{
		Feature->OnWeaponEquipped(this);
	}
}

void USwordmasterWeaponInstance::OnUnequip()
{
	Super::OnUnequip();

	USwordmasterEquipmentManagerComponent* Manager = Cast<USwordmasterEquipmentManagerComponent>(GetOuter());
	AActor* Owner = Manager->GetOwner();

	// Unlink anim layer
	USkeletalMeshComponent* Mesh = Owner->GetComponentByClass<USkeletalMeshComponent>();
	Mesh->UnlinkAnimClassLayers(AnimLayerClass);

	// Clear granted abilities
	if (IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(Owner))
	{
		USwordmasterAbilitySystemComponent* AbilitySystem = Cast<USwordmasterAbilitySystemComponent>(AbilitySystemInterface->GetAbilitySystemComponent());
		GrantedHandles.Reset(AbilitySystem);
	}

	for (USwordmasterWeaponFeature* Feature : WeaponFeatures)
	{
		Feature->OnWeaponUnequipped(this);
	}
}

FVector USwordmasterWeaponInstance::GetAttackBoundary_Implementation() const
{
	return AttackBoundary;
}

void USwordmasterWeaponInstance::SpawnTrailEffect_Implementation(UNiagaraSystem* SystemTemplate, FName AttachPointName)
{
	//USwordmasterEquipmentManagerComponent* Manager = Cast<USwordmasterEquipmentManagerComponent>(GetOuter());
	//if (AActor* Weapon = Manager->GetEquipmentActor(SwordmasterGameplayTags::Equipment_Slot_MainHand))
	//{
	//	if (UStaticMeshComponent* StaticMesh = Weapon->FindComponentByClass<UStaticMeshComponent>())
	//	{
	//		FRotator WeaponRotation = Weapon->GetActorRotation();
	//		WeaponRotation.Yaw += 180.0f;

	//		UNiagaraComponent* FX = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
	//			Weapon,
	//			SystemTemplate,
	//			Manager->GetOwner()->GetActorLocation(),
	//			FRotator::ZeroRotator,
	//			FVector::OneVector,
	//			true,
	//			true,
	//			ENCPoolMethod::None,
	//			true
	//		);
	//		FX->SetVectorParameter(FName("TrailRotation"), WeaponRotation.Vector());
	//	}
	//}
}

void USwordmasterWeaponInstance::DestroyTrailEffect_Implementation()
{

}

FVector USwordmasterWeaponInstance::GetSocketLocation_Implementation(FName SocketName) const
{
	USwordmasterEquipmentManagerComponent* Manager = Cast<USwordmasterEquipmentManagerComponent>(GetOuter());
	if (AActor* WeaponActor = Manager->GetEquipmentActor(SwordmasterGameplayTags::Equipment_Slot_MainHand))
	{
		if (UStaticMeshComponent* StaticMesh = WeaponActor->FindComponentByClass<UStaticMeshComponent>())
		{
			return StaticMesh->GetSocketLocation(SocketName);
		}
	}

	return Manager->GetOwner()->GetActorLocation();
}