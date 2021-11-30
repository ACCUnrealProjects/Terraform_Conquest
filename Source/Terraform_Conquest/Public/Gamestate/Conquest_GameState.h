// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "TeamsEnum.h"
#include "Conquest_GameState.generated.h"

/**
 * 
 */
UCLASS()
class TERRAFORM_CONQUEST_API AConquest_GameState : public AGameState
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score", meta = (AllowPrivateAccess = "true"))
	TMap<ETeam, int32> ScoreEachTeam;

protected:

public:

private:

protected:

public:
	AConquest_GameState();

	void AddScoreForTeam(ETeam Team, int32 ScoreToAdd);

	int32 GetScoreForTeam(ETeam Team) const;

};
