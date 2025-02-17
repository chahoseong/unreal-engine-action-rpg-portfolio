#include "UI/Controllers/SwordmasterOverlayController.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/SwordmasterAttributeSet.h"
#include "Blueprint/UserWidget.h"
#include "Interaction/SwordmasterInteractableComponent.h"
#include "Interaction/SwordmasterInteractorComponent.h"
#include "Player/SwordmasterPlayerState.h"

void USwordmasterOverlayController::InitializeEventBindings(APlayerController* NewPlayerController)
{
	PlayerController = NewPlayerController;
	ActiveInteractionContextWidget = NewObject<UUserWidget>(this, InteractionContextWidgetClass);

	ASwordmasterPlayerState* PlayerState = NewPlayerController->GetPlayerState<ASwordmasterPlayerState>();
	UAbilitySystemComponent* AbilitySystem = PlayerState->GetAbilitySystemComponent();

	AbilitySystem->GetGameplayAttributeValueChangeDelegate(USwordmasterAttributeSet::GetHealthAttribute())
		.AddLambda([this](const FOnAttributeChangeData& Data) { OnHealthChanged.Broadcast(Data.NewValue); });
	AbilitySystem->GetGameplayAttributeValueChangeDelegate(USwordmasterAttributeSet::GetMaxHealthAttribute())
		.AddLambda([this](const FOnAttributeChangeData& Data) { OnMaxHealthChanged.Broadcast(Data.NewValue); });
	AbilitySystem->GetGameplayAttributeValueChangeDelegate(USwordmasterAttributeSet::GetStaminaAttribute())
		.AddLambda([this](const FOnAttributeChangeData& Data) { OnStaminaChanged.Broadcast(Data.NewValue); });
	AbilitySystem->GetGameplayAttributeValueChangeDelegate(USwordmasterAttributeSet::GetMaxStaminaAttribute())
		.AddLambda([this](const FOnAttributeChangeData& Data) { OnMaxStaminaChanged.Broadcast(Data.NewValue); });

	if (USwordmasterInteractorComponent* Interactor = PlayerController->GetPawn()->FindComponentByClass<USwordmasterInteractorComponent>())
	{
		Interactor->OnInteractableFocused.AddUObject(this, &ThisClass::OnInteractableFocused);
		Interactor->OnInteractableUnfocused.AddUObject(this, &ThisClass::OnInteractableUnfocused);
	}
}

void USwordmasterOverlayController::BroadcastAttributes(USwordmasterAttributeSet* AttributeSet) const
{
	OnHealthChanged.Broadcast(AttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AttributeSet->GetMaxHealth());
	OnStaminaChanged.Broadcast(AttributeSet->GetStamina());
	OnMaxStaminaChanged.Broadcast(AttributeSet->GetMaxStamina());
}

void USwordmasterOverlayController::OnInteractableFocused(USwordmasterInteractableComponent* Interactable)
{
	if (PlayerController)
	{
		ActiveInteractionContextWidget->AddToViewport();
		FVector2D ScreenPosition;
		PlayerController->ProjectWorldLocationToScreen(Interactable->GetOwner()->GetActorLocation(), ScreenPosition);
		ActiveInteractionContextWidget->SetPositionInViewport(ScreenPosition);
	}

	K2_OnInteractableFocused(Interactable);
}

void USwordmasterOverlayController::OnInteractableUnfocused(USwordmasterInteractableComponent* Interactable)
{
	K2_OnInteractableUnfocused(Interactable);

	ActiveInteractionContextWidget->RemoveFromParent();
}
