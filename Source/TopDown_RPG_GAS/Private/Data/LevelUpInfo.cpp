// Copyright 13


#include "Data/LevelUpInfo.h"

int32 ULevelUpInfoDataAsset::FindLevelForXP(int32 XP)
{
	int Level = 1;
	bool bSearching = true;
	while (bSearching)
	{
		if (LevelUpInformation.Num() - 1 <= Level) return Level;

		if (XP >= LevelUpInformation[Level].LevelUpRequirement)
		{
			++Level;
		}
		else
		{
			bSearching = false;
		}	
	}
	return Level;
}
