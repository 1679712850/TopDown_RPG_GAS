// Copyright 13


#include "Character/AuraEnemy.h"

#include "TopDown_RPG_GAS/TopDown_RPG_GAS.h"


AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void AAuraEnemy::Highlight()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->CustomDepthStencilValue = HIGHLIGHT_CUSTOM_DEPTH;
	Weapon->SetRenderCustomDepth(true);
	Weapon->CustomDepthStencilValue = HIGHLIGHT_CUSTOM_DEPTH;
}

void AAuraEnemy::UnHighlight()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}