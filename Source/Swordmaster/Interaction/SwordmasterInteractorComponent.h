#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SwordmasterInteractorComponent.generated.h"

class USwordmasterInteractableComponent;
class USwordmasterInteractionDefinition;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnInteractableDelegate, USwordmasterInteractableComponent*);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SWORDMASTER_API USwordmasterInteractorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USwordmasterInteractorComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FOnInteractableDelegate OnInteractableFocused;
	FOnInteractableDelegate OnInteractableUnfocused;

private:
	void HandleHitActors(const TArray<FHitResult>& Hits);

protected:
	UPROPERTY(EditAnywhere)
	FVector Offset;

	UPROPERTY(EditAnywhere)
	float InteractionRadius = 10.0f;

	UPROPERTY(EditAnywhere)
	float InteractionMaxDistance = 150.0f;

	UPROPERTY(EditAnywhere)
	bool bDrawDebug = false;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<USwordmasterInteractionDefinition> CurrentInteraction;

	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<USwordmasterInteractableComponent> CurrentInteractable;
};
