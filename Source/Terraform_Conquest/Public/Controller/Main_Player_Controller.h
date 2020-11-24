// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
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

	class ABuildController* BuildingController = nullptr;
	
	class AMapController* MapController = nullptr;

	FGenericTeamId TeamId;

	void ExectutionAction();

	void CancelAction();

	void BuildingPlacement();

	void StartPowerSpawn();

	UFUNCTION()
	void MyPawnHasDied();

protected:

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "BuildingBlueprintSpawnTest")
	TSubclassOf<class ABuildingBluePrint> BuildingControllerSubClass;

	UPROPERTY(BlueprintReadOnly, Category = "ControlMode")
	ControlMode CurrentMode;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

public:

	AMain_Player_Controller();

	virtual void SetPawn(APawn* InPawn) override;

	void SetTeamID(FGenericTeamId TeamID);

	FGenericTeamId GetTeamId() const;
	
};
