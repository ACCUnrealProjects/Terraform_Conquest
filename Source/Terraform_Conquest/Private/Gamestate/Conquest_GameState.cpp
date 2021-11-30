// Alex Chatt Terraform_Conquest 2020

#include "Gamestate/Conquest_GameState.h"

AConquest_GameState::AConquest_GameState()
{
	ScoreEachTeam.Add(TTuple<ETeam, int32>(ETeam::Team1, 0));
	ScoreEachTeam.Add(TTuple<ETeam, int32>(ETeam::Team2, 0));
}

void AConquest_GameState::AddScoreForTeam(ETeam Team, int32 ScoreToAdd)
{
	if (ScoreEachTeam.Contains(Team))
	{
		ScoreEachTeam[Team] += ScoreToAdd;
	}
}

int32 AConquest_GameState::GetScoreForTeam(ETeam Team) const
{
	if (ScoreEachTeam.Contains(Team))
	{
		return ScoreEachTeam[Team];
	}
	
	return 0;
}
