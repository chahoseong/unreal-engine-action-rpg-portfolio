#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SwordmasterOverlayController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOverlayAttributeChanged, float, NewValue);

class USwordmasterAttributeSet;
class USwordmasterInteractableComponent;

UCLASS(Blueprintable, BlueprintType)
class SWORDMASTER_API USwordmasterOverlayController : public UObject
{
	GENERATED_BODY()
	
public:
	void InitializeEventBindings(APlayerController* PlayerController);
	void BroadcastAttributes(USwordmasterAttributeSet* AttributeSet) const;

	UPROPERTY(BlueprintAssignable)
	FOnOverlayAttributeChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnOverlayAttributeChanged OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnOverlayAttributeChanged OnStaminaChanged;

	UPROPERTY(BlueprintAssignable)
	FOnOverlayAttributeChanged OnMaxStaminaChanged;

protected:
	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnInteractableFocused")
	void K2_OnInteractableFocused(USwordmasterInteractableComponent* Interactable);
	
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "OnInteractableUnfocused")
	void K2_OnInteractableUnfocused(USwordmasterInteractableComponent* Interactable);

private:
	void OnInteractableFocused(USwordmasterInteractableComponent* Interactable);
	void OnInteractableUnfocused(USwordmasterInteractableComponent* Interactable);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UUserWidget> InteractionContextWidgetClass;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UUserWidget> ActiveInteractionContextWidget;

private:
	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController;
};
