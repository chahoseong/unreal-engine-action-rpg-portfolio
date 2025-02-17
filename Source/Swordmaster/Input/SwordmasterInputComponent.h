// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "SwordmasterInputConfig.h"
#include "SwordmasterInputComponent.generated.h"

struct FGameplayTag;

UCLASS(Config = Input)
class SWORDMASTER_API USwordmasterInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	template <typename UserClass, typename FuncType>
	void BindNativeAction(const USwordmasterInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Callback, bool bLogIfNotFound);

	template <typename UserClass, typename PressedFuncType, typename HeldFuncType, typename ReleasedFuncType>
	void BindAbilityActions(const USwordmasterInputConfig* InputConfig, UserClass* Object, PressedFuncType CallbackOnPressed, HeldFuncType CallbackOnHeld, ReleasedFuncType CallbackOnReleased);
};

template<typename UserClass, typename FuncType>
void USwordmasterInputComponent::BindNativeAction(const USwordmasterInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Callback, bool bLogIfNotFound)
{
	check(InputConfig);

	if (const UInputAction* Action = InputConfig->FindNativeInputActionWithTag(InputTag, bLogIfNotFound))
	{
		BindAction(Action, TriggerEvent, Object, Callback);
	}
}

template<typename UserClass, typename PressedFuncType, typename HeldFuncType, typename ReleasedFuncType>
void USwordmasterInputComponent::BindAbilityActions(const USwordmasterInputConfig* InputConfig, UserClass* Object, PressedFuncType CallbackOnPressed, HeldFuncType CallbackOnHeld, ReleasedFuncType CallbackOnReleased)
{
	check(InputConfig);

	for (const FSwordmasterInputAction& Action : InputConfig->AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (CallbackOnPressed)
			{
				BindAction(Action.InputAction, ETriggerEvent::Started, Object, CallbackOnPressed, Action.InputTag);
			}

			if (CallbackOnHeld)
			{
				BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, CallbackOnHeld, Action.InputTag);
			}

			if (CallbackOnReleased)
			{
				BindAction(Action.InputAction, ETriggerEvent::Completed, Object, CallbackOnReleased, Action.InputTag);
			}
		}
	}
}
