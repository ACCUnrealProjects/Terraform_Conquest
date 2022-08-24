// Alex Chatt Terraform_Conquest 2020

#include "GameModes/TerraformGameMode.h"
#include "Gamestate/Conquest_GameState.h"
#include "MyGameSettings.h"

ATerraformGameMode::ATerraformGameMode()
{
	GameStateClass = AConquest_GameState::StaticClass();
}

void ATerraformGameMode::StartPlay()
{
	Super::StartPlay();
	FGenericTeamId::SetAttitudeSolver(&UMyGameSettings::GetAttitude);
}

void ATerraformGameMode::CreatePlayerPawn(TSubclassOf <class APawn> PawnType, APlayerController* PCon, FTransform SpawnTransform)
{
	if (!PCon || !HasAuthority())
	{
		return;
	}

	FActorSpawnParameters PawnParams;
	PawnParams.Owner = PCon;
	APawn* SpawnPawn = GetWorld()->SpawnActor<APawn>(PawnType, SpawnTransform, PawnParams);
	PCon->Possess(SpawnPawn);
}
