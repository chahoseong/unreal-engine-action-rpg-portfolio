// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SwordmasterEnemyAttributesRow.generated.h"

USTRUCT()
struct SWORDMASTER_API FSwordmasterEnemyAttributesRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int32 EnemyId;

	UPROPERTY(EditDefaultsOnly, Category="Primary Attributes")
	float Strength;

	UPROPERTY(EditDefaultsOnly, Category="Primary Attributes")
	float Intellect;

	UPROPERTY(EditDefaultsOnly, Category="Primary Attributes")
	float Agility;

	UPROPERTY(EditDefaultsOnly, Category="Primary Attributes")
	float Will;

	UPROPERTY(EditDefaultsOnly, Category="Secondary Attributes")
	float MaxHealth;

	UPROPERTY(EditDefaultsOnly, Category="Secondary Attributes")
	float MaxStamina;

	UPROPERTY(EditDefaultsOnly, Category="Combat Attributes")
	float WeaponDamage;

	UPROPERTY(EditDefaultsOnly, Category="Combat Attributes")
	float Armor;
};
