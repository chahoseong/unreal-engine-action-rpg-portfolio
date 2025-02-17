#include "UI/SwordmasterHUD.h"
#include "UI/Controllers/SwordmasterOverlayController.h"
#include "UI/Widget/SwordmasterUserWidget.h"
#include "AbilitySystem/SwordmasterAttributeSet.h"
#include "Player/SwordmasterPlayerState.h"

void ASwordmasterHUD::ShowOverlay()
{
	USwordmasterUserWidget* OverlayWidget = CreateWidget<USwordmasterUserWidget>(GetWorld(), OverlayWidgetClass);
	USwordmasterOverlayController* OverlayController = GetOverlayController();
	OverlayWidget->SetController(OverlayController);
	
	ASwordmasterPlayerState* PlayerState = PlayerOwner->GetPlayerState<ASwordmasterPlayerState>();
	USwordmasterAttributeSet* AttributeSet = PlayerState->GetAttributeSet<USwordmasterAttributeSet>();
	OverlayController->BroadcastAttributes(AttributeSet);

	OverlayWidget->AddToViewport();
}

USwordmasterOverlayController* ASwordmasterHUD::GetOverlayController() const
{
	if (!CachedOverlayController)
	{
		CachedOverlayController = NewObject<USwordmasterOverlayController>(const_cast<ASwordmasterHUD*>(this), OverlayControllerClass);
		CachedOverlayController->InitializeEventBindings(PlayerOwner);
	}
	return CachedOverlayController;
}
