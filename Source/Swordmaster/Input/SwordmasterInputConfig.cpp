#include "Input/SwordmasterInputConfig.h"
#include "SwordmasterLogChannels.h"

const UInputAction* USwordmasterInputConfig::FindNativeInputActionWithTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FSwordmasterInputAction& Action : NativeInputActions)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogSwordmaster, Error, TEXT("Can't find NativeInputAction for InputTag [%s] on InputConfig [%s]."), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}

const UInputAction* USwordmasterInputConfig::FindAbilityInputActionWithTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FSwordmasterInputAction& Action : AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogSwordmaster, Error, TEXT("Can't find AbilityInputAction for InputTag [%s] on InputConfig [%s]."), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}
