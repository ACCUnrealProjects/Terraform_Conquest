// Alex Chatt Terraform_Conquest 2020

#include "Pawns/TeamActionPawn.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ATeamActionPawn::ATeamActionPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

/*void ATeamActionPawn::SetUpMyStimulis()
{
	Stimulus = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("MyAIStim"));
	Stimulus->RegisterForSense(TSubclassOf<UAISense_Sight>());
	Stimulus->RegisterWithPerceptionSystem();
}*/

void ATeamActionPawn::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Replicate everywhere
	DOREPLIFETIME(ATeamActionPawn, TeamId);

	//Replicate to owner client and server only
	//DOREPLIFETIME_CONDITION(AVehicle, WantToFire, COND_OwnerOnly);

	//Replicate to none owner client and server only
}

void ATeamActionPawn::SetTeamID(ETeam NewTeamID)
{
	ServerSetTeamID(NewTeamID);
}

bool ATeamActionPawn::ServerSetTeamID_Validate(ETeam NewTeamID)
{
	return true;
}

void ATeamActionPawn::ServerSetTeamID_Implementation(ETeam NewTeamID)
{
	Tags.Remove(FName(GetTeamName(TeamId)));
	TeamId = NewTeamID;
	Tags.Add(FName(GetTeamName(TeamId)));
}
