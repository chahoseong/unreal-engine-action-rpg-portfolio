#include "Equipments/SwordmasterEquipmentInstance.h"
#include "Equipments/SwordmasterEquipmentFeature.h"
#include "Equipments/SwordmasterEquipmentAttributeRow.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "SwordmasterGameplayTags.h"
#include "SwordmasterDataTableHelper.h"

int32 USwordmasterEquipmentInstance::GetItemId() const
{
	return ItemId;
}

const FGameplayTag& USwordmasterEquipmentInstance::GetSlotTag() const
{
	return SlotTag;
}

void USwordmasterEquipmentInstance::OnEquip()
{
	for (USwordmasterEquipmentFeature* Feature : EquipmentFeatures)
	{
		Feature->OnInstanceEquipped(this);
	}

	if (UAbilitySystemComponent* AbilitySystem = GetAbilitySystemComponent())
	{
		FGameplayEffectContextHandle ContextHandle = AbilitySystem->MakeEffectContext();
		ContextHandle.AddSourceObject(this);

		TMap<FGameplayTag, float> SetByCallerTagMagnitudes;
		FSwordmasterEquipmentAttributeRow* Row = SwordmasterDataTableHelper::BinarySearchBy<FSwordmasterEquipmentAttributeRow>(AttributesTable, ItemId, [](const FSwordmasterEquipmentAttributeRow* Row) { return Row->ItemId; });
		if (Row)
		{
			SetByCallerTagMagnitudes.Add(SwordmasterGameplayTags::Attribute_Primary_Strength, Row->Strength);
			SetByCallerTagMagnitudes.Add(SwordmasterGameplayTags::Attribute_Primary_Intellect, Row->Intellect);
			SetByCallerTagMagnitudes.Add(SwordmasterGameplayTags::Attribute_Primary_Agility, Row->Agility);
			SetByCallerTagMagnitudes.Add(SwordmasterGameplayTags::Attribute_Primary_Will, Row->Will);

			SetByCallerTagMagnitudes.Add(SwordmasterGameplayTags::Attribute_Secondary_MaxHealth, Row->MaxHealth);
			SetByCallerTagMagnitudes.Add(SwordmasterGameplayTags::Attribute_Secondary_MaxStamina, Row->MaxStamina);

			SetByCallerTagMagnitudes.Add(SwordmasterGameplayTags::Attribute_Combat_WeaponDamage, Row->WeaponDamage);
			SetByCallerTagMagnitudes.Add(SwordmasterGameplayTags::Attribute_Combat_Armor, Row->Armor);
		}

		for (TSubclassOf<UGameplayEffect> Effect : GameplayEffectsToGrant)
		{
			const FGameplayEffectSpecHandle SpecHandle = AbilitySystem->MakeOutgoingSpec(Effect, 1.0f, ContextHandle);
			SpecHandle.Data->SetByCallerTagMagnitudes.Add(SwordmasterGameplayTags::GameplayEvent_EquipItem, ItemId);
			SpecHandle.Data->SetByCallerTagMagnitudes.Append(SetByCallerTagMagnitudes);
			FActiveGameplayEffectHandle ActiveEffectHandle = AbilitySystem->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data, AbilitySystem);
			ActiveGameplayEffects.Add(ActiveEffectHandle);
		}
	}
}

void USwordmasterEquipmentInstance::OnUnequip()
{
	if (UAbilitySystemComponent* AbilitySystem = GetAbilitySystemComponent())
	{
		for (FActiveGameplayEffectHandle ActiveEffect : ActiveGameplayEffects)
		{
			AbilitySystem->RemoveActiveGameplayEffect(ActiveEffect);
		}
		ActiveGameplayEffects.Reset();
	}

	for (USwordmasterEquipmentFeature* Feature : EquipmentFeatures)
	{
		Feature->OnInstanceUnequipped(this);
	}
}

UAbilitySystemComponent* USwordmasterEquipmentInstance::GetAbilitySystemComponent() const
{
	UActorComponent* Outer = Cast<UActorComponent>(GetOuter());
	return UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Outer->GetOwner());
}
