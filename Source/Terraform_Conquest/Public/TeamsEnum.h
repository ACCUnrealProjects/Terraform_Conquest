// Alex Chatt Terraform_Conquest 2020
// https://forums.unrealengine.com/development-discussion/c-gameplay-programming/1569711-how-do-i-use-the-ai-perception-teams

#pragma once

#include "CoreMinimal.h"
#include "UObject/Class.h"
#include "GenericTeamAgentInterface.h"

UENUM(BlueprintType)
enum class TeamsEnum : uint8
{
	Neutral,
	Team1,
	Team2
};

