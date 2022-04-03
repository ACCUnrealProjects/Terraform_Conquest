#include "TeamsEnum.h"

FString GetTeamName(const ETeam TeamENum)
{
	return UEnum::GetValueAsString(TEnumAsByte<ETeam>(TeamENum).GetValue());
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

FColor GetTeamColour(ETeam Team)
{
	return TeamColours[Team];
}
