#include "AbilitySystem/Abilities/SwordmasterGameplayAbility.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Player/SwordmasterPlayerController.h"
#include "SwordmasterGameplayTags.h"
#include "SwordmasterFunctionLibrary.h"

ESwordmasterAbilityActivationPolicy USwordmasterGameplayAbility::GetActivationPolicy() const
{
    return ActivationPolicy;
}

AController* USwordmasterGameplayAbility::GetControllerFromActorInfo() const
{
    if (CurrentActorInfo)
    {
        if (AController* Controller = CurrentActorInfo->PlayerController.Get())
        {
            return Controller;
        }

        AActor* Actor = CurrentActorInfo->OwnerActor.Get();
        while (Actor)
        {
            if (AController* Controller = Cast<AController>(Actor))
            {
                return Controller;
            }

            if (APawn* Pawn = Cast<APawn>(Actor))
            {
                return Pawn->GetController();
            }

            Actor = Actor->GetOwner();
        }
    }
    return nullptr;
}

void USwordmasterGameplayAbility::AddGameplayTagIfNotContainsFromActorInfo(const FGameplayTag& TagToAdd)
{
    USwordmasterFunctionLibrary::AddGameplayTagIfNotContains(GetOwningActorFromActorInfo(), TagToAdd);
}

void USwordmasterGameplayAbility::AddGameplayTagFromActorInfo(const FGameplayTag& TagToAdd)
{
    if (UAbilitySystemComponent* AbilitySystem = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwningActorFromActorInfo()))
    {
        AbilitySystem->AddLooseGameplayTag(TagToAdd);
    }
}

void USwordmasterGameplayAbility::RemoveGameplayTagIfContainsFromActorInfo(const FGameplayTag& TagToRemove)
{
    USwordmasterFunctionLibrary::RemoveGameplayTagIfContains(GetOwningActorFromActorInfo(), TagToRemove);
}

void USwordmasterGameplayAbility::RemoveGameplayTagFromActorInfo(const FGameplayTag& TagToRemove)
{
    if (UAbilitySystemComponent* AbilitySystem = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwningActorFromActorInfo()))
    {
        AbilitySystem->RemoveLooseGameplayTag(TagToRemove);
    }
}

void USwordmasterGameplayAbility::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
    if (UAbilitySystemComponent* AbilitySystem = ActorInfo->AbilitySystemComponent.Get())
    {
        if (FGameplayAbilitySpec* AbilitySpec = AbilitySystem->FindAbilitySpecFromHandle(Handle))
        {
            if (AbilitySpec->InputPressed)
            {
                K2_OnInputPressed();
            }
        }
    }
}

void USwordmasterGameplayAbility::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
    if (UAbilitySystemComponent* AbilitySystem = ActorInfo->AbilitySystemComponent.Get())
    {
        if (FGameplayAbilitySpec* AbilitySpec = AbilitySystem->FindAbilitySpecFromHandle(Handle))
        {
            if (!AbilitySpec->InputPressed)
            {
                K2_OnInputReleased();
            }
        }
    }
}

void USwordmasterGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    if (ActivationPolicy == ESwordmasterAbilityActivationPolicy::OnGiven)
    {
        if (ActorInfo)
        {
            ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
        }
    }

    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void USwordmasterGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
    Super::OnGiveAbility(ActorInfo, Spec);

    if (ActivationPolicy == ESwordmasterAbilityActivationPolicy::OnGiven)
    {
        if (ActorInfo && !Spec.IsActive())
        {
            ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
        }
    }
}
