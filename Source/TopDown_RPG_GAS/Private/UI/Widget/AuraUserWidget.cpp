// Copyright 13


#include "UI/Widget/AuraUserWidget.h"

void UAuraUserWidget::SetWidgetController(UObject* InController)
{
	WidgetController = InController;
	OnWidgetControllerSet();
}
