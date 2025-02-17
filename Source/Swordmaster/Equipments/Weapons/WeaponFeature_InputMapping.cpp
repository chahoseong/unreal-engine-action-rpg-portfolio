#include "Equipments/Weapons/WeaponFeature_InputMapping.h"
#include "Equipments/Weapons/SwordmasterWeaponInstance.h"
#include "Equipments/SwordmasterEquipmentManagerComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "Input/SwordmasterInputGlobals.h"
#include "SwordmasterFunctionLibrary.h"

void UWeaponFeature_InputMapping::OnWeaponEquipped(USwordmasterWeaponInstance* Instance)
{
	USwordmasterEquipmentManagerComponent* Manager = Cast<USwordmasterEquipmentManagerComponent>(Instance->GetOuter());
	if (ACharacter* OwningCharacter = Manager->GetOwner<ACharacter>())
	{
		APlayerController* PlayerController = OwningCharacter->GetController<APlayerController>();
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		USwordmasterInputGlobals* InputGlobals = USwordmasterFunctionLibrary::GetInputGlobals(this);
		int32 Priority = InputGlobals ? InputGlobals->GetWeaponInputMappingPriority() : 0;
		Subsystem->AddMappingContext(InputMapping, Priority);
	}
}

void UWeaponFeature_InputMapping::OnWeaponUnequipped(USwordmasterWeaponInstance* Instance)
{
	USwordmasterEquipmentManagerComponent* Manager = Cast<USwordmasterEquipmentManagerComponent>(Instance->GetOuter());
	if (ACharacter* OwningCharacter = Manager->GetOwner<ACharacter>())
	{
		APlayerController* PlayerController = OwningCharacter->GetController<APlayerController>();
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		Subsystem->RemoveMappingContext(InputMapping);
	}
}
