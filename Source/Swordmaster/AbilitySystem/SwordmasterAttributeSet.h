#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystem/SwordmasterAbilitySystemComponent.h"
#include "SwordmasterAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class SWORDMASTER_API USwordmasterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	USwordmasterAttributeSet();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	/*
	 * Primary Attributes
	 */
	ATTRIBUTE_ACCESSORS(USwordmasterAttributeSet, Strength);
	ATTRIBUTE_ACCESSORS(USwordmasterAttributeSet, Intellect);
	ATTRIBUTE_ACCESSORS(USwordmasterAttributeSet, Agility);
	ATTRIBUTE_ACCESSORS(USwordmasterAttributeSet, Will);

	/*
	 * Secondary Attributes
	 */
	ATTRIBUTE_ACCESSORS(USwordmasterAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(USwordmasterAttributeSet, MaxStamina);

	/*
	 * Vital Attributes
	 */
	ATTRIBUTE_ACCESSORS(USwordmasterAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(USwordmasterAttributeSet, Stamina);

	/*
	* Combat Attributes
	*/
	ATTRIBUTE_ACCESSORS(USwordmasterAttributeSet, WeaponDamage);
	ATTRIBUTE_ACCESSORS(USwordmasterAttributeSet, Armor);
	ATTRIBUTE_ACCESSORS(USwordmasterAttributeSet, Knockdown);
	ATTRIBUTE_ACCESSORS(USwordmasterAttributeSet, BlockedDamageReduction);

	/*
	 * Meta Attributes
	 */
	ATTRIBUTE_ACCESSORS(USwordmasterAttributeSet, IncomingDamage);

private:
	/*
	 * Primary Attributes
	 */
	UPROPERTY(BlueprintReadOnly, Category="Swordmaster|Primary Attributes", Meta=(AllowPrivateAccess=true))
	FGameplayAttributeData Strength;

	UPROPERTY(BlueprintReadOnly, Category="Swordmaster|Primary Attributes", Meta=(AllowPrivateAccess=true))
	FGameplayAttributeData Intellect;

	UPROPERTY(BlueprintReadOnly, Category="Swordmaster|Primary Attributes", Meta=(AllowPrivateAccess=true))
	FGameplayAttributeData Agility;

	UPROPERTY(BlueprintReadOnly, Category="Swordmaster|Primary Attributes", Meta=(AllowPrivateAccess=true))
	FGameplayAttributeData Will;

	/*
	 * Secondary Attributes
	 */
	UPROPERTY(BlueprintReadOnly, Category="Swordmaster|Secondary Attributes", Meta=(AllowPrivateAccess=true))
	FGameplayAttributeData MaxHealth;

	UPROPERTY(BlueprintReadOnly, Category="Swordmaster|Secondary Attributes", Meta=(AllowPrivateAccess=true))
	FGameplayAttributeData MaxStamina;

	/*
	 * Vital Attributes
	 */
	UPROPERTY(BlueprintReadOnly, Category="Swordmaster|Vital Attributes", Meta=(AllowPrivateAccess=true))
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, Category="Swordmaster|Vital Attributes", Meta=(AllowPrivateAccess=true))
	FGameplayAttributeData Stamina;

	/*
	 * Combat Attributes
	 */
	UPROPERTY(BlueprintReadOnly, Category="Swordmaster|Combat Attributes", Meta=(AllowPrivateAccess=true))
	FGameplayAttributeData WeaponDamage;

	UPROPERTY(BlueprintReadOnly, Category="Swordmaster|Combat Attributes", Meta=(AllowPrivateAccess=true))
	FGameplayAttributeData Armor;

	UPROPERTY(BlueprintReadOnly, Category="Swordmaster|Combat Attributes", Meta=(AllowPrivateAccess=true))
	FGameplayAttributeData Knockdown;

	UPROPERTY(BlueprintReadOnly, Category = "Swordmaster|Combat Attributes", Meta=(AllowPrivateAccess=true))
	FGameplayAttributeData BlockedDamageReduction;

	/*
	 * Meta Attributes
	 */
	UPROPERTY(BlueprintReadOnly, Category="Swordmaster|Meta Attributes", Meta=(AllowPrivateAccess=true))
	FGameplayAttributeData IncomingDamage;
};
