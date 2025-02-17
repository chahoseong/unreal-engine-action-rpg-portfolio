#include "Interaction/SwordmasterInteractorComponent.h"
#include "Interaction/SwordmasterInteractableComponent.h"
#include "Interaction/SwordmasterInteractionDefinition.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SwordmasterGameplayTags.h"
#include "SwordmasterFunctionLibrary.h"

USwordmasterInteractorComponent::USwordmasterInteractorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USwordmasterInteractorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (USwordmasterFunctionLibrary::DoesActorHaveGameplayTag(GetOwner(), SwordmasterGameplayTags::Gameplay_InteractionAbilityBlocked))
	{
		return;
	}

	if (!USwordmasterFunctionLibrary::DoesActorHaveGameplayTag(GetOwner(), SwordmasterGameplayTags::Character_Status_Interacting))
	{
		if (const UWorld* World = GEngine->GetWorldFromContextObject(GetOwner(), EGetWorldErrorMode::LogAndReturnNull))
		{
			TArray<FHitResult> Hits;
			FVector Start = GetOwner()->GetActorLocation() + Offset;
			FVector End = Start + GetOwner()->GetActorForwardVector() * InteractionMaxDistance;

			UKismetSystemLibrary::SphereTraceMulti(
				GetOwner(),
				Start,
				End,
				InteractionRadius,
				UEngineTypes::ConvertToTraceType(ECC_Visibility),
				false,
				TArray<AActor*>(),
				(bDrawDebug ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None),
				Hits,
				true
			);

			HandleHitActors(Hits);
		}
	}
}

void USwordmasterInteractorComponent::HandleHitActors(const TArray<FHitResult>& Hits)
{
	bool bAlreadyInteractionQueried = false;
	bool bStartInteractionQuery = false;

	for (const FHitResult& Hit : Hits)
	{
		if (USwordmasterInteractableComponent* Interactable = Hit.GetActor()->FindComponentByClass<USwordmasterInteractableComponent>())
		{
			if (CurrentInteractable.IsValid() && CurrentInteractable.Get() == Interactable)
			{
				bAlreadyInteractionQueried = true;
			}
			else
			{
				CurrentInteraction = Interactable->QueryInteraction(GetOwner());
				CurrentInteractable = Interactable;
				USwordmasterFunctionLibrary::AddGameplayTagIfNotContains(GetOwner(), CurrentInteraction->GetInteractionTag());
				OnInteractableFocused.Broadcast(CurrentInteractable.Get());
				bStartInteractionQuery = true;
			}
			break;
		}
	}

	if (!bAlreadyInteractionQueried && !bStartInteractionQuery)
	{
		OnInteractableUnfocused.Broadcast(CurrentInteractable.Get());

		if (CurrentInteraction != nullptr)
		{
			USwordmasterFunctionLibrary::RemoveGameplayTagIfContains(GetOwner(), CurrentInteraction->GetInteractionTag());
		}

		CurrentInteraction = nullptr;
		CurrentInteractable = nullptr;
	}
}
