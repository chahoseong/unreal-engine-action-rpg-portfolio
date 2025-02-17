#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SwordmasterCombatFunctionLibrary.generated.h"

class USwordmasterAttributeSet;

struct FAttackDamageParameters
{
	float WeaponDamage;
	float Strength;
};

UCLASS()
class SWORDMASTER_API USwordmasterCombatFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static float CalculateAttackDamage(const FAttackDamageParameters& Params);
};
