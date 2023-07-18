// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "UObject/Class.h"
#include "Containers/Map.h"
#include "GenericTeamAgentInterface.h"

UENUM(BlueprintType)
enum class ETeam : uint8
{
	Neutral = 0 UMETA(DisplayName = "Neutral"),
	Team1 = 1 UMETA(DisplayName = "Team1"),
	Team2 = 2 UMETA(DisplayName = "Team2"),
	Team3 = 3 UMETA(DisplayName = "Team3"),
	Team4 = 4 UMETA(DisplayName = "Team4")
};

static const TMap<ETeam, FString> TeamStringMap
{
	{ETeam::Neutral, "Neutral"},
	{ETeam::Team1, "Team1"},
	{ETeam::Team2, "Team2"},
	{ETeam::Team3, "Team3"},
	{ETeam::Team4, "Team4"},
};

static const TMap<ETeam, FColor> TeamColours
{
	{ETeam::Neutral, FColor(1, 1, 1)},
	{ETeam::Team1, FColor(1, 0, 0)},
	{ETeam::Team2, FColor(0, 1, 0)},
	{ETeam::Team3, FColor(1, 0, 1)},
	{ETeam::Team4, FColor(0, 1, 1)},
};

FString GetTeamName(const ETeam TeamENum);

ETeam GetTeamFromString(const FString TeamName);

bool TeamTagCheck(const ETeam TeamENum, const TArray<FString> Tags);

FColor GetTeamColour(const ETeam Team);
