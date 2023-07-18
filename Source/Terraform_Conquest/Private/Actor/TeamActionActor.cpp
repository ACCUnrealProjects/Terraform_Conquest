// Alex Chatt Terraform_Conquest 2020

#include "Actor/TeamActionActor.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ATeamActionActor::ATeamActionActor()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ATeamActionActor::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Replicate everywhere
	DOREPLIFETIME(ATeamActionActor, TeamId);

	//Replicate to owner client and server only
	//DOREPLIFETIME_CONDITION(AVehicle, WantToFire, COND_OwnerOnly);

	//Replicate to none owner client and server only
}

void ATeamActionActor::SetTeamID(ETeam NewTeamID)
{
	ServerSetTeamID(NewTeamID);
}

bool ATeamActionActor::ServerSetTeamID_Validate(ETeam NewTeamID)
{
	return true;
}

void ATeamActionActor::ServerSetTeamID_Implementation(ETeam NewTeamID)
{
	Tags.Remove(FName(GetTeamName(TeamId)));
	TeamId = NewTeamID;
	Tags.Add(FName(GetTeamName(TeamId)));
}


