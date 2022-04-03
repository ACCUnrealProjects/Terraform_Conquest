// Alex Chatt Terraform_Conquest 2020
// https://forums.unrealengine.com/development-discussion/c-gameplay-programming/1569711-how-do-i-use-the-ai-perception-teams

#pragma once

#include "CoreMinimal.h"
#include "UObject/Class.h"
#include "GenericTeamAgentInterface.h"

UENUM(BlueprintType)
enum class ETeam : uint8
{
	None = 0 UMETA(DisplayName = "None"),
	Neutral = 1 UMETA(DisplayName = "Neutral"),
	Team1 = 2 UMETA(DisplayName = "Team1"),
	Team2 = 3 UMETA(DisplayName = "Team2"),
	Last = 4
};

static const TMap<ETeam, FColor> TeamColours
{
	{ETeam::Neutral, FColor(1, 1, 1)},
	{ETeam::Team1, FColor(1, 0, 0)},
	{ETeam::Team2, FColor(0, 1, 0)}
};

FString GetTeamName(const ETeam TeamENum);

bool TeamTagCheck(const ETeam TeamENum, const TArray<FString> Tags);

FColor GetTeamColour(ETeam Team);
