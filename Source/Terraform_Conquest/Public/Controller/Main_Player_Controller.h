// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
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
	
	UFUNCTION()
	void MyPawnHasDied();

	virtual void SetPawn(APawn* InPawn) override;

	void BuildingPlacementTest();

protected:

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

public:

	AMain_Player_Controller();
	
};
