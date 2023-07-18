#include "Utility/TeamsEnum.h"

FString GetTeamName(const ETeam TeamENum)
{
	if (TeamStringMap.Contains(TeamENum))
	{
		return TeamStringMap[TeamENum];
	}
	return "Neutral";
}

ETeam GetTeamFromString(const FString TeamName)
{
	for (auto TeamString : TeamStringMap)
	{
		if (TeamString.Value == TeamName)
		{
			return TeamString.Key;
		}
	}

	return ETeam::Neutral;
}

bool TeamTagCheck(const ETeam TeamENum, const TArray<FString> Tags)
{
	for (auto Tag : Tags)
	{
		if (GetTeamName(TeamENum) == Tag)
		{
			return true;
		}
	}

	return false;
}

FColor GetTeamColour(const ETeam Team)
{
	return TeamColours[Team];
}
