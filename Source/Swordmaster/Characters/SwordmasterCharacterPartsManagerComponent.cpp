#include "Characters/SwordmasterCharacterPartsManagerComponent.h"
#include "GameFramework/Character.h"
#include "SkeletalMergingLibrary.h"
#include "SwordmasterGameplayTags.h"
#include "SwordmasterLogChannels.h"

USwordmasterCharacterPartsManagerComponent::USwordmasterCharacterPartsManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void USwordmasterCharacterPartsManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* OwningCharacter = GetOwner<ACharacter>();
	check(OwningCharacter);

	OwningSkeletalMeshComponent = OwningCharacter->GetMesh();
}

void USwordmasterCharacterPartsManagerComponent::UpdateCurrentParts()
{
	if (bCurrentPartsChanged)
	{
		FSkeletalMeshMergeParams Params;
		for (const TPair<FGameplayTag, FCharacterPartInstance>& Entry : CurrentParts)
		{
			Params.MeshesToMerge.Append(Entry.Value.Meshes);
		}
		Params.Skeleton = OwningCharacterSkeleton;

		USkeletalMesh* Merged = USkeletalMergingLibrary::MergeMeshes(Params);
		OwningSkeletalMeshComponent->SetSkeletalMesh(Merged, false);

		ReapplyLinkedAnimInstances();

		bCurrentPartsChanged = false;
	}
}

void USwordmasterCharacterPartsManagerComponent::ReapplyLinkedAnimInstances()
{
	const TArray<UAnimInstance*> LinkedAnimInstances = Cast<const USkeletalMeshComponent>(OwningSkeletalMeshComponent)->GetLinkedAnimInstances();

	for (UAnimInstance* Elem : LinkedAnimInstances)
	{
		OwningSkeletalMeshComponent->UnlinkAnimClassLayers(Elem->GetClass());
	}

	for (UAnimInstance* Elem : LinkedAnimInstances)
	{
		OwningSkeletalMeshComponent->LinkAnimClassLayers(Elem->GetClass());
	}
}

void USwordmasterCharacterPartsManagerComponent::ChangeCurrentPart(const FGameplayTag& PartTag, const TArray<USkeletalMesh*>& Meshes, bool bAsDefault)
{
	if (!IsTagValid(PartTag))
	{
		return;
	}

	FCharacterPartInstance& CurrentPartInstance = CurrentParts.FindOrAdd(PartTag);
	CurrentPartInstance.Meshes.Reset();
	if (Meshes.Num() > 0)
	{
		CurrentPartInstance.Meshes.Append(Meshes);
	}
	bCurrentPartsChanged = true;

	if (bAsDefault)
	{
		FCharacterPartInstance& Entry = DefaultParts.FindOrAdd(PartTag);
		Entry.Meshes = Meshes;
	}
}

void USwordmasterCharacterPartsManagerComponent::RemoveCurrentPart(const FGameplayTag& PartTag)
{
	if (!IsTagValid(PartTag))
	{
		return;
	}

	CurrentParts.Remove(PartTag);

	if (const FCharacterPartInstance* DefaultPartInstance = DefaultParts.Find(PartTag))
	{
		ChangeCurrentPart(PartTag, DefaultPartInstance->Meshes);
	}
}

bool USwordmasterCharacterPartsManagerComponent::IsTagValid(const FGameplayTag& PartTag, bool bLogIfNotValid) const
{
	if (!PartTag.MatchesTag(SwordmasterGameplayTags::Character_Part))
	{
		UE_LOG(LogSwordmaster, Warning, TEXT("Invalid Character Part Tag [%s]"), *PartTag.ToString());
		return false;
	}

	return true;
}
