#include "System/SwordmasterGameInstance.h"
#include "Input/SwordmasterInputGlobals.h"

void USwordmasterGameInstance::Init()
{
	Super::Init();

	ActiveInputGlobals = NewObject<USwordmasterInputGlobals>(this, InputGlobalsClass.Get());
}

USwordmasterInputGlobals* USwordmasterGameInstance::GetInputGlobals() const
{
	return ActiveInputGlobals;
}
