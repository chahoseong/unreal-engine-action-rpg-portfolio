#pragma once

#include "CoreMinimal.h"
#include "SwordmasterItemDefinition.generated.h"

UENUM(BlueprintType)
enum class ESwordmasterItemCategory : uint8
{
	None,
	Sword,
	Shield,
	Armor,
	Accessory,
};

USTRUCT(Blueprintable, BlueprintType)
struct SWORDMASTER_API FSwordmasterItemDefinition : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 ItemId;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMesh> Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ESwordmasterItemCategory Category;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaxQuantity = 1;
};
