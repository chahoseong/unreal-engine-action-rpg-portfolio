#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "SwordmasterInteractionDefinition.generated.h"

class UAnimMontage;

UCLASS(Blueprintable, BlueprintType)
class SWORDMASTER_API USwordmasterInteractionDefinition : public UObject
{
	GENERATED_BODY()

public:
	const FGameplayTag& GetInteractionTag() const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText InteractionName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag InteractionTag;
};
