#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SwordmasterGameInstance.generated.h"

class USwordmasterInputGlobals;

UCLASS()
class SWORDMASTER_API USwordmasterGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;

	USwordmasterInputGlobals* GetInputGlobals() const;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<USwordmasterInputGlobals> InputGlobalsClass;

private:
	UPROPERTY()
	TObjectPtr<USwordmasterInputGlobals> ActiveInputGlobals;
};
