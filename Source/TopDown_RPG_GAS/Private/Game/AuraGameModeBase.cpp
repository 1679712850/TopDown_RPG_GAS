// Copyright 13


#include "Game/AuraGameModeBase.h"

#include "AuraGameplayTags.h"


void AAuraGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	// todo:仅用于开发调试
	FAuraGameplayTags::InitializeNativeGameplayTags();
}
