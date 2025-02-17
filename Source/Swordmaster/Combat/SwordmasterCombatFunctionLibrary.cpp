#include "Combat/SwordmasterCombatFunctionLibrary.h"

float USwordmasterCombatFunctionLibrary::CalculateAttackDamage(const FAttackDamageParameters& Params)
{
	return Params.WeaponDamage + Params.Strength / 3.0f;
}
