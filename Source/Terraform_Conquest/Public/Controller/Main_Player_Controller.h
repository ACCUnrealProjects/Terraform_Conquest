// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerController.h"
#include "Main_Player_Controller.generated.h"

/**
 * 
 */
UCLASS()
class TERRAFORM_CONQUEST_API AMain_Player_Controller : public APlayerController
{
	GENERATED_BODY()

private:

	class AMapControllerV2* MapController = nullptr;

	FGenericTeamId TeamId;

	UFUNCTION()
	void MyPawnHasDied();

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

public:

	AMain_Player_Controller();

	virtual void SetPawn(APawn* InPawn) override;

	void SetTeamID(FGenericTeamId TeamID);

	FGenericTeamId GetTeamId() const;
	
};
