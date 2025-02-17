#include "AbilitySystem/Executions/SwordmaterDamageExecution.h"
#include "AbilitySystem/SwordmasterAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Combat/SwordmasterCombatFunctionLibrary.h"
#include "Equipments/SwordmasterEquipmentInstance.h"
#include "Equipments/SwordmasterEquipmentAttributeRow.h"
#include "GameplayEffectTypes.h"
#include "SwordmasterGameplayTags.h"

struct FDamageStatics
{
	FGameplayEffectAttributeCaptureDefinition WeaponDamageDef;
	FGameplayEffectAttributeCaptureDefinition ArmorDef;

	FGameplayEffectAttributeCaptureDefinition StrengthDef;
	FGameplayEffectAttributeCaptureDefinition IntellectDef;
	FGameplayEffectAttributeCaptureDefinition AgilityDef;
	FGameplayEffectAttributeCaptureDefinition WillDef;

	TMap<FGameplayTag, FGameplayAttribute> TagsToAttributes;
	
	FDamageStatics()
	{
		WeaponDamageDef = FGameplayEffectAttributeCaptureDefinition(USwordmasterAttributeSet::GetWeaponDamageAttribute(), EGameplayEffectAttributeCaptureSource::Source, false);
		ArmorDef = FGameplayEffectAttributeCaptureDefinition(USwordmasterAttributeSet::GetArmorAttribute(), EGameplayEffectAttributeCaptureSource::Target, false);

		StrengthDef = FGameplayEffectAttributeCaptureDefinition(USwordmasterAttributeSet::GetStrengthAttribute(), EGameplayEffectAttributeCaptureSource::Source, false);
		IntellectDef = FGameplayEffectAttributeCaptureDefinition(USwordmasterAttributeSet::GetIntellectAttribute(), EGameplayEffectAttributeCaptureSource::Source, false);
		AgilityDef = FGameplayEffectAttributeCaptureDefinition(USwordmasterAttributeSet::GetAgilityAttribute(), EGameplayEffectAttributeCaptureSource::Target, false);
		WillDef = FGameplayEffectAttributeCaptureDefinition(USwordmasterAttributeSet::GetWillAttribute(), EGameplayEffectAttributeCaptureSource::Target, false);

		TagsToAttributes.Add(SwordmasterGameplayTags::Attribute_Combat_WeaponDamage, USwordmasterAttributeSet::GetWeaponDamageAttribute());
		TagsToAttributes.Add(SwordmasterGameplayTags::Attribute_Combat_Armor, USwordmasterAttributeSet::GetArmorAttribute());
		TagsToAttributes.Add(SwordmasterGameplayTags::Attribute_Primary_Strength, USwordmasterAttributeSet::GetStrengthAttribute());
		TagsToAttributes.Add(SwordmasterGameplayTags::Attribute_Primary_Intellect, USwordmasterAttributeSet::GetIntellectAttribute());
		TagsToAttributes.Add(SwordmasterGameplayTags::Attribute_Primary_Agility, USwordmasterAttributeSet::GetAgilityAttribute());
		TagsToAttributes.Add(SwordmasterGameplayTags::Attribute_Primary_Will, USwordmasterAttributeSet::GetWillAttribute());
	}
};

static const FDamageStatics& DamageStatics()
{
	static FDamageStatics Statics;
	return Statics;
}

USwordmaterDamageExecution::USwordmaterDamageExecution()
{
	RelevantAttributesToCapture.Add(DamageStatics().WeaponDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().StrengthDef);
	RelevantAttributesToCapture.Add(DamageStatics().IntellectDef);
	RelevantAttributesToCapture.Add(DamageStatics().AgilityDef);
	RelevantAttributesToCapture.Add(DamageStatics().WillDef);
}

void USwordmaterDamageExecution::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParams;
	EvaluationParams.SourceTags = SourceTags;
	EvaluationParams.TargetTags = TargetTags;

	/*
	 * Calculate source damage
	 */
	float SourceWeaponDamage = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().WeaponDamageDef, EvaluationParams, SourceWeaponDamage);

	float SourceStrength = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().StrengthDef, EvaluationParams, SourceStrength);

	FAttackDamageParameters AttackDamageParams{ SourceWeaponDamage, SourceStrength };
	float Damage = USwordmasterCombatFunctionLibrary::CalculateAttackDamage(AttackDamageParams);

	/*
	 * Calculate target damage defense
	 */
	float TargetArmor = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaluationParams, TargetArmor);

	float TargetAgility = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().AgilityDef, EvaluationParams, TargetAgility);

	float TargetWill = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().WillDef, EvaluationParams, TargetWill);

	Damage -= (TargetArmor + TargetAgility / 2.0f + TargetWill / 5.0f);
	
	if (Damage < 0) {
		Damage = 0.0f;
	}

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(
		USwordmasterAttributeSet::GetIncomingDamageAttribute(),
		EGameplayModOp::Additive,
		Damage
	));
}
