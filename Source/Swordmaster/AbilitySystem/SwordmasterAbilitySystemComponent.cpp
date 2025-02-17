#include "AbilitySystem/SwordmasterAbilitySystemComponent.h"
#include "Abilities/SwordmasterGameplayAbility.h"
#include "SwordmasterGameplayTags.h"

USwordmasterAbilitySystemComponent::USwordmasterAbilitySystemComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void USwordmasterAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& InputTag)
{
	if (InputTag.IsValid())
	{
		for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items)
		{
			if (AbilitySpec.Ability && AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
			{
				InputPressedSpecHandles.AddUnique(AbilitySpec.Handle);
				InputHeldSpecHandles.AddUnique(AbilitySpec.Handle);
			}
		}
	}
}

void USwordmasterAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (InputTag.IsValid())
	{
		for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items)
		{
			if (AbilitySpec.Ability && AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
			{
				InputReleasedSpecHandles.AddUnique(AbilitySpec.Handle);
				InputHeldSpecHandles.Remove(AbilitySpec.Handle);
			}
		}
	}
}

void USwordmasterAbilitySystemComponent::ProcessAbilityInput(float DeltaTime, bool bGamePaused)
{
	if (HasMatchingGameplayTag(SwordmasterGameplayTags::Gameplay_AbilityInputBlocked))
	{
		ClearAbilityInput();
		return;
	}

	static TArray<FGameplayAbilitySpecHandle> AbilitiesToActivate;
	AbilitiesToActivate.Reset();

	//
	// Process all abilities that activate when the input is held.
	//
	for (const FGameplayAbilitySpecHandle& Handle : InputHeldSpecHandles)
	{
		if (const FGameplayAbilitySpec* Spec = FindAbilitySpecFromHandle(Handle))
		{
			if (Spec->Ability && !Spec->IsActive())
			{
				const USwordmasterGameplayAbility* AbilityDefault = CastChecked<USwordmasterGameplayAbility>(Spec->Ability);
				if (AbilityDefault->GetActivationPolicy() == ESwordmasterAbilityActivationPolicy::WhileInputActive)
				{
					AbilitiesToActivate.AddUnique(Spec->Handle);
				}
			}
		}
	}

	//
	// Process all abilities that had their input pressed this frame.
	//
	for (const FGameplayAbilitySpecHandle& Handle : InputPressedSpecHandles)
	{
		if (FGameplayAbilitySpec* Spec = FindAbilitySpecFromHandle(Handle))
		{
			if (Spec->Ability)
			{
				Spec->InputPressed = true;

				if (Spec->IsActive())
				{
					AbilitySpecInputPressed(*Spec);
				}
				else
				{
					const USwordmasterGameplayAbility* AbilityDefault = CastChecked<USwordmasterGameplayAbility>(Spec->Ability);
					if (AbilityDefault->GetActivationPolicy() == ESwordmasterAbilityActivationPolicy::OnInputTriggered)
					{
						AbilitiesToActivate.AddUnique(Spec->Handle);
					}
				}
			}
		}
	}

	for (const FGameplayAbilitySpecHandle& AbilitySpecHandle : AbilitiesToActivate)
	{
		TryActivateAbility(AbilitySpecHandle);
	}

	//
	// Process all abilities that had their input released this frame.
	//
	for (const FGameplayAbilitySpecHandle& Handle : InputReleasedSpecHandles)
	{
		if (FGameplayAbilitySpec* Spec = FindAbilitySpecFromHandle(Handle))
		{
			if (Spec->Ability)
			{
				Spec->InputPressed = false;

				if (Spec->IsActive())
				{
					AbilitySpecInputReleased(*Spec);
				}
			}
		}
	}

	InputPressedSpecHandles.Reset();
	InputReleasedSpecHandles.Reset();
}

void USwordmasterAbilitySystemComponent::ClearAbilityInput()
{
	InputPressedSpecHandles.Reset();
	InputReleasedSpecHandles.Reset();
	InputHeldSpecHandles.Reset();
}
