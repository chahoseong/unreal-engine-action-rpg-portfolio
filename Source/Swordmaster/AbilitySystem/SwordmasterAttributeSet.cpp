#include "AbilitySystem/SwordmasterAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "SwordmasterGameplayTags.h"
#include "AbilitySystemBlueprintLibrary.h"

USwordmasterAttributeSet::USwordmasterAttributeSet()
{
}

void USwordmasterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}

	if (Attribute == GetStaminaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxStamina());
	}

	if (Attribute == GetKnockdownAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.0f);
	}
}

void USwordmasterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(), 0.0f, GetMaxStamina()));
	}

	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		const float AppliedDamage = GetIncomingDamage();
		SetIncomingDamage(0.0f);

		if (AppliedDamage > 0.0f)
		{
			const float NewHealth = GetHealth() - AppliedDamage;
			SetHealth(FMath::Clamp(NewHealth, 0.0f, GetMaxHealth()));

			if (NewHealth <= 0.0f)
			{
				Data.Target.AddLooseGameplayTag(SwordmasterGameplayTags::Character_Status_Dead);
			}
		}
	}

	if (Data.EvaluatedData.Attribute == GetKnockdownAttribute())
	{
		SetKnockdown(FMath::Max(0.0f, GetKnockdown()));
	}
}
