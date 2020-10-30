// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Main_Player_Controller.generated.h"

UENUM(BlueprintType)
enum class ControlMode : uint8
{
	UnitSelected        UMETA(DisplayName = "UnitSelected"),
	BuildingPlacement	UMETA(DisplayName = "BuildingPlacement"),
	Selection			UMETA(DisplayName = "Selection"),
	FreeDrive		    UMETA(DisplayName = "FreeDrive"),
};

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

	UPROPERTY(BlueprintReadOnly, Category = "ControlMode")
	ControlMode CurrentMode;

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

public:

	AMain_Player_Controller();
	
};
