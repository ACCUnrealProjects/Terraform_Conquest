// Copyright Epic Games, Inc. All Rights Reserved.


#include "Terraform_ConquestGameModeBase.h"
#include "Gamestate/Conquest_GameState.h"

ATerraform_ConquestGameModeBase::ATerraform_ConquestGameModeBase()
{
	GameStateClass = AConquest_GameState::StaticClass();
}

void ATerraform_ConquestGameModeBase::StartPlay()
{
	Super::StartPlay();
}