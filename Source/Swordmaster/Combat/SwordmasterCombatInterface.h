#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SwordmasterCombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USwordmasterCombatInterface : public UInterface
{
	GENERATED_BODY()
};

class USwordmasterCombatComponent;

class SWORDMASTER_API ISwordmasterCombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual USwordmasterCombatComponent* GetSwordmasterCombatComponent() const = 0;
};
