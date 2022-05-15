// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Utility/TeamsEnum.h"
#include "TeamActionPawn.generated.h"

UCLASS()
class TERRAFORM_CONQUEST_API ATeamActionPawn : public APawn, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(Replicated)
	ETeam TeamId = ETeam::Neutral;

private:
	//void SetUpMyStimulis();

protected:
	//class UAIPerceptionStimuliSourceComponent* Stimulus = nullptr;

public:	
	ATeamActionPawn();

	/** Property replication */
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void SetTeamID(ETeam NewTeamID);
	UFUNCTION(reliable, server, WithValidation)
	void ServerSetTeamID(ETeam NewTeamID);
	virtual bool ServerSetTeamID_Validate(ETeam NewTeamID);
	virtual void ServerSetTeamID_Implementation(ETeam NewTeamID);

	ETeam GetTeamId() const { return TeamId; }
	virtual FGenericTeamId GetGenericTeamId() const override { return uint8(TeamId); };
};
