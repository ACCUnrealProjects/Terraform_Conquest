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

	UPROPERTY(Replicated)
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

	virtual void SetPawn(APawn* InPawn) override;

	/** Property replication */
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "NewActorForMap"))
		void NewActorForMap(bool bIsStatic, AActor *OwnerActor);

	UFUNCTION(BlueprintCallable, reliable, server, meta = (DisplayName = "CreateNewPawn"))
		void ServerCreateNewPawn(TSubclassOf <class APawn> PawnType, FTransform SpawnTransform);
	void ServerCreateNewPawn_Implementation(TSubclassOf <class APawn> PawnType, FTransform SpawnTransform);

	UFUNCTION(BlueprintCallable, reliable, server, meta = (DisplayName = "SetTeamID"))
		void ServerSetTeamID(ETeam NewTeamID);
	void ServerSetTeamID_Implementation(ETeam NewTeamID);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetTeamId"))
		ETeam GetTeamId() const { return TeamId; };
};
