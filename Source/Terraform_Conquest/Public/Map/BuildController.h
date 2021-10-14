// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Actor.h"
#include "../Map/TileIndex.h"
#include "BuildController.generated.h"

UCLASS()
class TERRAFORM_CONQUEST_API ABuildController : public AActor
{
	GENERATED_BODY()
	
private:	

	FGenericTeamId TeamId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapController", meta = (AllowPrivateAccess = "true"))
	class AMapController* MapController = nullptr;

	class ABuildingBluePrint* BuildingToBuild = nullptr;

	TArray<class AMapTile*> TilesBuildingWillBeOn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	ABuildController();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CreateBuildingBlueprint(TSubclassOf<class ABuildingBluePrint> BluePrintToSpawn);

	void SetBluePrintLocation(FVector Pos, FTileIndex CurrentTile);

	bool AttemptedToBuild(FString &FailedMessage);

	void CancelBuild();

	void SetTeamID(FGenericTeamId TeamID);

	FGenericTeamId GetTeamId() const;
};
