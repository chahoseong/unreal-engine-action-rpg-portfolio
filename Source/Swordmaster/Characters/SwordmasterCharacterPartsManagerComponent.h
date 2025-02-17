#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "SwordmasterCharacterPartsManagerComponent.generated.h"

USTRUCT()
struct FCharacterPartInstance
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<TObjectPtr<USkeletalMesh>> Meshes;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SWORDMASTER_API USwordmasterCharacterPartsManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USwordmasterCharacterPartsManagerComponent();

	void UpdateCurrentParts();

	void ChangeCurrentPart(const FGameplayTag& PartTag, const TArray<USkeletalMesh*>& Meshes, bool bAsDefault = false);
	void RemoveCurrentPart(const FGameplayTag& PartTag);

protected:
	virtual void BeginPlay() override;

private:
	bool IsTagValid(const FGameplayTag& PartTag, bool bLogIfNotValid = true) const;
	void ReapplyLinkedAnimInstances();

protected:
	UPROPERTY(EditDefaultsOnly, Category="Swordmaster|CharacterParts")
	TObjectPtr<USkeleton> OwningCharacterSkeleton;

	UPROPERTY(EditDefaultsOnly, Category="Swordmaster|CharacterParts")
	TSubclassOf<UAnimInstance> CharacterAnimInstance;

private:
	UPROPERTY(VisibleAnywhere, Category = "Swordmaster|CharacterParts")
	TObjectPtr<USkeletalMeshComponent> OwningSkeletalMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Swordmaster|CharacterParts")
	TMap<FGameplayTag, FCharacterPartInstance> CurrentParts;

	UPROPERTY(VisibleAnywhere, Category = "Swordmaster|CharacterParts")
	TMap<FGameplayTag, FCharacterPartInstance> DefaultParts;

	bool bCurrentPartsChanged = false;
};
