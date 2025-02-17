#include "UI/Widget/SwordmasterUserWidget.h"

void USwordmasterUserWidget::SetController(UObject* NewController)
{
	Controller = NewController;
	OnControllerChanged(NewController);
}
