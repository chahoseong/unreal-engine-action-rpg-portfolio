#include "Characters/SwordmasterPlayerCharacter.h"
#include "Characters/SwordmasterCharacterPartsManagerComponent.h"
#include "Characters/SwordmasterCharacterPartRow.h"
#include "AbilitySystem/SwordmasterAbilitySystemComponent.h"
#include "AbilitySystem/SwordmasterAttributeSet.h"
#include "Camera/CameraComponent.h"
#include "Combat/SwordmasterCombatComponent.h"
#include "Combat/SwordmasterComboSystemComponent.h"
#include "Combat/SwordmasterCombatWeapon.h"
#include "Engine/AssetManager.h"
#include "Equipments/SwordmasterEquipmentManagerComponent.h"
#include "Equipments/SwordmasterEquipmentSet.h"
#include "Equipments/SwordmasterEquipmentInstance.h"
#include "Equipments/Weapons/SwordmasterWeaponInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interaction/SwordmasterInteractorComponent.h"
#include "MotionWarpingComponent.h"
#include "Player/SwordmasterPlayerState.h"
#include "SwordmasterGameplayTags.h"
#include "SwordmasterDataTableHelper.h"

ASwordmasterPlayerCharacter::ASwordmasterPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritYaw = false;
	CameraBoom->bInheritRoll = false;
	CameraBoom->SetupAttachment(GetRootComponent());

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);

	CharacterPartsManager = CreateDefaultSubobject<USwordmasterCharacterPartsManagerComponent>(TEXT("CharacterPartsManager"));
	EquipmentManager = CreateDefaultSubobject<USwordmasterEquipmentManagerComponent>(TEXT("EquipmentManager"));

	CombatComponent = CreateDefaultSubobject<USwordmasterCombatComponent>(TEXT("Combat"));
	ComboSystemComponent = CreateDefaultSubobject<USwordmasterComboSystemComponent>(TEXT("ComboSystem"));

	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarping"));

	InteractorComponent = CreateDefaultSubobject<USwordmasterInteractorComponent>(TEXT("Interactor"));
}

void ASwordmasterPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilityActorInfo();
	ApplyStartupAbilitySet();
}

void ASwordmasterPlayerCharacter::InitAbilityActorInfo()
{
	ASwordmasterPlayerState* SwordmasterPlayerState = GetPlayerState<ASwordmasterPlayerState>();
	check(SwordmasterPlayerState);

	AbilitySystemComponent = SwordmasterPlayerState->GetAbilitySystemComponent();
	AbilitySystemComponent->InitAbilityActorInfo(SwordmasterPlayerState, this);

	AttributeSet = SwordmasterPlayerState->GetAttributeSet();
}

void ASwordmasterPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitAttributes();
	LoadCharacterParts();
}

void ASwordmasterPlayerCharacter::LoadCharacterParts()
{
	if (CharacterPartsDataTable.IsPending())
	{
		FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
		Streamable.RequestAsyncLoad(CharacterPartsDataTable.ToSoftObjectPath(), [this] {
			LoadCharacterParts();
		});
	}
	else
	{
		UDataTable* DataTable = CharacterPartsDataTable.Get();
		
		TArray<FSwordmasterCharacterPartRow*> Rows;
		DataTable->GetAllRows(TEXT(""), Rows);
		auto KeySelector = [](const FSwordmasterCharacterPartRow* Row) { return Row->Id; };

		for (int32 PartId : InitialCharacterParts)
		{
			if (FSwordmasterCharacterPartRow* Row = SwordmasterDataTableHelper::BinarySearchBy(Rows, PartId, KeySelector))
			{	
				CharacterPartsManager->ChangeCurrentPart(Row->Tag, Row->Meshes, true);
			}
		}
		CharacterPartsManager->UpdateCurrentParts();

		OnCharacterPartsLoaded();
	}
}

void ASwordmasterPlayerCharacter::OnCharacterPartsLoaded()
{
	EquipmentManager->Equip(DefaultWeaponInstance);
	EquipmentManager->OnEquipmentChanged.AddUObject(this, &ThisClass::OnEquipmentChanged);
}

void ASwordmasterPlayerCharacter::InitAttributes()
{
	if (ASwordmasterPlayerState* OwningPlayerState = GetPlayerState<ASwordmasterPlayerState>())
	{
		int PlayerLevel = OwningPlayerState->GetLevel();
		ApplyEffectToSelf(DefaultPrimaryAttributes, PlayerLevel);
		ApplyEffectToSelf(DefaultSecondaryAttributes, PlayerLevel);
		ApplyEffectToSelf(DefaultVitalAttributes, PlayerLevel);
		ApplyEffectToSelf(DefaultCombatAttributes, PlayerLevel);
	}
}

void ASwordmasterPlayerCharacter::OnEquipmentChanged(const FOnEquipmentChangeData& Data)
{
	if (Data.SlotTag == SwordmasterGameplayTags::Equipment_Slot_MainHand)
	{
		if (!Data.NewEquipment)
		{
			EquipmentManager->Equip(DefaultWeaponInstance);
		}
		else
		{
			CombatComponent->SetWeapon(Data.NewEquipment);
		}
	}

	CharacterPartsManager->UpdateCurrentParts();
}

void ASwordmasterPlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector TargetLocation = GetActorLocation() + GetActorForwardVector() * 100.0f;

	FVector LastMovementInput = GetLastMovementInputVector();
	if (!LastMovementInput.IsNearlyZero())
	{
		TargetLocation = GetActorLocation() + LastMovementInput * 100.0f;
	}
}

USpringArmComponent* ASwordmasterPlayerCharacter::GetSpringArm() const
{
	return CameraBoom;
}

USwordmasterCombatComponent* ASwordmasterPlayerCharacter::GetSwordmasterCombatComponent() const
{
	return CombatComponent;
}

FGenericTeamId ASwordmasterPlayerCharacter::GetTeamId() const
{
	IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(GetController());
	return TeamAgent->GetGenericTeamId();
}
