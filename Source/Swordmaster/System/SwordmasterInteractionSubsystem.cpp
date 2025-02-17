#include "System/SwordmasterInteractionSubsystem.h"
#include "Interaction/SwordmasterInteractionDefinition.h"

USwordmasterInteractionDefinition* USwordmasterInteractionSubsystem::GetInteraction(TSubclassOf<USwordmasterInteractionDefinition> Class) const
{
	if (USwordmasterInteractionDefinition * Interaction = CachedInteractions.FindRef(Class.Get()))
	{
		return Interaction;
	}

	USwordmasterInteractionDefinition* Interaction = NewObject<USwordmasterInteractionDefinition>(const_cast<USwordmasterInteractionSubsystem*>(this), Class);
	CachedInteractions.Add(Class.Get(), Interaction);
	return Interaction;
}
