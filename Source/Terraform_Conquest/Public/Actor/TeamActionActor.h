// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utility/TeamsEnum.h"
#include "TeamActionActor.generated.h"

UCLASS()
class TERRAFORM_CONQUEST_API ATeamActionActor : public AActor, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Replicated)
	ETeam TeamId = ETeam::Neutral;

protected:

public:	

	// Sets default values for this actor's properties
	ATeamActionActor();

	/** Property replication */
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void SetTeamID(ETeam NewTeamID);
	UFUNCTION(reliable, server, WithValidation)
	void ServerSetTeamID(ETeam NewTeamID);
	virtual bool ServerSetTeamID_Validate(ETeam NewTeamID);
	virtual void ServerSetTeamID_Implementation(ETeam NewTeamID);

	UFUNCTION(BlueprintCallable)
	ETeam GetTeamId() const { return TeamId; }
	virtual FGenericTeamId GetGenericTeamId() const override { return uint8(TeamId); };

};
