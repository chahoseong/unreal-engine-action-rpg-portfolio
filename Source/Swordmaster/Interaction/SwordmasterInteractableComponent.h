// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "SwordmasterInteractableComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteract, AActor*, Interactor);

class USwordmasterInteractionDefinition;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SWORDMASTER_API USwordmasterInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USwordmasterInteractableComponent();

	USwordmasterInteractionDefinition* QueryInteraction(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	void InteractWith(AActor* Actor);

	UPROPERTY(BlueprintAssignable)
	FOnInteract OnInteract;

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<USwordmasterInteractionDefinition> InteractionClass;
};
