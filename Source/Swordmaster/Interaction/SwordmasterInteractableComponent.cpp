#include "Interaction/SwordmasterInteractableComponent.h"
#include "Interaction/SwordmasterInteractionDefinition.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "System/SwordmasterInteractionSubsystem.h"

USwordmasterInteractableComponent::USwordmasterInteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USwordmasterInteractableComponent::BeginPlay()
{
	Super::BeginPlay();

}

USwordmasterInteractionDefinition* USwordmasterInteractableComponent::QueryInteraction(AActor* Actor)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(GetOwner(), EGetWorldErrorMode::LogAndReturnNull))
	{
		USwordmasterInteractionSubsystem* Subsystem = World->GetSubsystem<USwordmasterInteractionSubsystem>();
		check(Subsystem);
		return Subsystem->GetInteraction(InteractionClass);
	}

	return nullptr;
}

void USwordmasterInteractableComponent::InteractWith(AActor* Actor)
{
	OnInteract.Broadcast(Actor);
}
