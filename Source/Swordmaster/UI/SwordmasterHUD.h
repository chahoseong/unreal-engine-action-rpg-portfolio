#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SwordmasterHUD.generated.h"

class USwordmasterUserWidget;
class USwordmasterOverlayController;

UCLASS()
class SWORDMASTER_API ASwordmasterHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	void ShowOverlay();

	USwordmasterOverlayController* GetOverlayController() const;


protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<USwordmasterUserWidget> OverlayWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<USwordmasterOverlayController> OverlayControllerClass;

private:
	UPROPERTY()
	TObjectPtr<USwordmasterUserWidget> ActiveOverlayWidget;

	UPROPERTY()
	mutable TObjectPtr<USwordmasterOverlayController> CachedOverlayController;
};
