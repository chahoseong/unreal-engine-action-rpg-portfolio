#pragma once

#include "CoreMinimal.h"
#include "SwordmasterCharacterPartRow.generated.h"

USTRUCT(Blueprintable, BlueprintType, DisplayName="Swordmaster Character Parts")
struct SWORDMASTER_API FSwordmasterCharacterPartRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int32 Id;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag Tag;

	UPROPERTY(EditDefaultsOnly)
	TArray<USkeletalMesh*> Meshes;
};
