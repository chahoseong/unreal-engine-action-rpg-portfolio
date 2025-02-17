#include "Characters/SwordmasterEnemyCharacter.h"
#include "Characters/SwordmasterEnemyAttributesRow.h"
#include "AbilitySystem/SwordmasterAbilitySystemComponent.h"
#include "AbilitySystem/SwordmasterAttributeSet.h"
#include "Combat/SwordmasterCombatComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Engine/AssetManager.h"
#include "Equipments/Weapons/SwordmasterWeaponInstance.h"
#include "GameplayEffect.h"
#include "SwordmasterGameplayTags.h"
#include "SwordmasterDataTableHelper.h"
#include "UI/Widget/SwordmasterUserWidget.h"

ASwordmasterEnemyCharacter::ASwordmasterEnemyCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<USwordmasterAbilitySystemComponent>(TEXT("AbilitySystem"));
	AttributeSet = CreateDefaultSubobject<USwordmasterAttributeSet>(TEXT("AttributeSet"));
	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	HealthBar->SetupAttachment(GetRootComponent());

	CombatComponent = CreateDefaultSubobject<USwordmasterCombatComponent>(TEXT("CombatComponent"));
}

void ASwordmasterEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitAbilityActorInfo();
	LoadInitialAttributes();

	ApplyStartupAbilitySet();
}

void ASwordmasterEnemyCharacter::SetHealthBarWidgetController()
{
	if (USwordmasterUserWidget* UserWidget = Cast<USwordmasterUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		UserWidget->SetController(this);
	}
}

void ASwordmasterEnemyCharacter::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void ASwordmasterEnemyCharacter::LoadInitialAttributes()
{
	if (AttributesTable.IsPending())
	{
		FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
		Streamable.RequestAsyncLoad(AttributesTable.ToSoftObjectPath(), [this] {
			LoadInitialAttributes();
		});
	}
	else
	{
		FSwordmasterEnemyAttributesRow* Row = SwordmasterDataTableHelper::BinarySearchBy<FSwordmasterEnemyAttributesRow>(AttributesTable.Get(), EnemyId,
			[](const FSwordmasterEnemyAttributesRow* Row) { return Row->EnemyId; });
		if (ensureMsgf(Row, TEXT("Invalid enemy id: [%d]. check enemy attributes table: [%s]"), EnemyId, *AttributesTable.GetAssetName()))
		{
			if (USwordmasterAttributeSet* SwordmasterAttributeSet = Cast<USwordmasterAttributeSet>(AttributeSet))
			{
				SwordmasterAttributeSet->SetStrength(Row->Strength);
				SwordmasterAttributeSet->SetIntellect(Row->Intellect);
				SwordmasterAttributeSet->SetAgility(Row->Agility);
				SwordmasterAttributeSet->SetWill(Row->Will);
				SwordmasterAttributeSet->SetMaxHealth(Row->MaxHealth);
				SwordmasterAttributeSet->SetHealth(Row->MaxHealth);
				SwordmasterAttributeSet->SetMaxStamina(Row->MaxStamina);
				SwordmasterAttributeSet->SetStamina(Row->MaxStamina);
				SwordmasterAttributeSet->SetWeaponDamage(Row->WeaponDamage);
				SwordmasterAttributeSet->SetArmor(Row->Armor);
			}

			OnInitialAttributesLoaded();
		}
	}
}

void ASwordmasterEnemyCharacter::OnInitialAttributesLoaded()
{
	SetHealthBarWidgetController();

	if (USwordmasterAttributeSet* SwordmasterAttributeSet = Cast<USwordmasterAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(USwordmasterAttributeSet::GetHealthAttribute())
			.AddLambda([this](const FOnAttributeChangeData& Data) {
				if (Data.NewValue <= 0)
				{
					Die();
				}
				OnHealthChanged.Broadcast(Data.NewValue);
			});

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(USwordmasterAttributeSet::GetMaxHealthAttribute())
			.AddLambda([this](const FOnAttributeChangeData& Data) {
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			});

		OnHealthChanged.Broadcast(SwordmasterAttributeSet->GetHealth());
		OnMaxHealthChanged.Broadcast(SwordmasterAttributeSet->GetMaxHealth());
	}
}

void ASwordmasterEnemyCharacter::Die()
{
	HealthBar->SetVisibility(false, true);

	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	
	OnDead.Broadcast();
}

FGenericTeamId ASwordmasterEnemyCharacter::GetTeamId() const
{
	IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(GetController());
	return TeamAgent->GetGenericTeamId();
}

bool ASwordmasterEnemyCharacter::IsDead_Implementation() const
{
	if (USwordmasterAttributeSet* SwordmasterAttributeSet = Cast<USwordmasterAttributeSet>(AttributeSet))
	{
		return SwordmasterAttributeSet->GetHealth() <= 0.0f;
	}
	return false;
}
