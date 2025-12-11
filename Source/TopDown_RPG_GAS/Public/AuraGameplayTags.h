#pragma once
#include "GameplayTagContainer.h"

/**
 * AuraGameplayTags
 *
 * Singleton containing native Gameplay Tags
 */

struct FAuraGameplayTags
{
public:
	static const FAuraGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();
protected:
	FGameplayTag Attributes_Secondary_Armor;
private:
	static FAuraGameplayTags GameplayTags;
};
