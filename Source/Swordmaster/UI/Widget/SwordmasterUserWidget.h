#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SwordmasterUserWidget.generated.h"

UCLASS()
class SWORDMASTER_API USwordmasterUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetController(UObject* NewController);

protected:
	UFUNCTION(BlueprintImplementableEvent, DisplayName="Change Controller")
	void OnControllerChanged(UObject* NewController);
	
protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> Controller;
};
