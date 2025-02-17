#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GenericTeamAgentInterface.h"
#include "SwordmasterCombatTarget.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class USwordmasterCombatTarget : public UInterface
{
	GENERATED_BODY()
};

class SWORDMASTER_API ISwordmasterCombatTarget
{
	GENERATED_BODY()

public:
	virtual FGenericTeamId GetTeamId() const = 0;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool IsDead() const;
};
