// Copyright 13


#include "AuraHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/Widget/AuraUserWidget.h"

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();

	auto Widget = CreateWidget<UAuraUserWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();
}
