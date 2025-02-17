#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "GameplayTagContainer.h"

#include "SwordmasterPlayerController.generated.h"

class USwordmasterAbilitySystemComponent;
class UInputMappingContext;
class USwordmasterInputConfig;
class UInputAction;
struct FInputActionValue;

UCLASS()
class SWORDMASTER_API ASwordmasterPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
public:
	ASwordmasterPlayerController();

	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;
	virtual void PlayerTick(float DeltaTime) override;

	virtual FGenericTeamId GetGenericTeamId() const override;

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

private:
	USwordmasterAbilitySystemComponent* GetSwordmasterAbilitySystem() const;

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);
	void Input_SwitchTarget_Triggered(const FInputActionValue& InputActionValue);
	void Input_SwitchTarget_Completed(const FInputActionValue& InputActionValue);

	void Input_AbilityInputTagPressed(FGameplayTag InputTag);
	void Input_AbilityInputTagHeld(FGameplayTag InputTag);
	void Input_AbilityInputTagReleased(FGameplayTag InputTag);

private:
	UPROPERTY(EditAnywhere, Category="Camera", meta=(UIMin="-89.9", UIMax="0.0"))
	float CameraMinPitch = -89.9f;

	UPROPERTY(EditAnywhere, Category="Camera", meta=(UIMin="0.0", UIMax="+89.9"))
	float CameraMaxPitch = +89.9f;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputMappingContext> DefaultInputMapping;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<USwordmasterInputConfig> InputConfig;

	FGenericTeamId TeamId;

	FVector2D SwitchDirection;
};
