// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerController.h"
#include "Utility/TeamsEnum.h"
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

	ETeam TeamId;
	
	TArray<TPair<AActor*,bool>> NewMiniMapIcon;

private:

	UFUNCTION()
	void MyPawnHasDied();

protected:

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	UFUNCTION()
	void MiniMapIconSetUp();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "AddActorMarkerToMap"))
	void AddActorMarkerToMap(bool bIsStatic, AActor* OwnerActor);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UISetup")
	bool bMiniMapSetUp = false;

public:

	AMain_Player_Controller();

	virtual void Tick(float DeltaTime) override;

	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "NewActorForMap"))
	void NewActorForMap(bool bIsStatic, AActor *OwnerActor);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetTeamID"))
	void SetTeamID(ETeam TeamID) { TeamId = TeamID; };

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetTeamId"))
	ETeam GetTeamId() const { return TeamId; };
};
