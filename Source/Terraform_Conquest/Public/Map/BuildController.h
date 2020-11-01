// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Map/TileIndex.h"
#include "BuildController.generated.h"

UCLASS()
class TERRAFORM_CONQUEST_API ABuildController : public AActor
{
	GENERATED_BODY()
	
private:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapController", meta = (AllowPrivateAccess = "true"))
	class AMapController* MapController = nullptr;

	class ABuildingBluePrint* BuildingToBuild = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:	
	// Sets default values for this actor's properties
	ABuildController();

	void CreateBuildingBlueprint(TSubclassOf<class ABuildingBluePrint> BluePrintToSpawn);

	void SetBluePrintLocation(FVector Pos, FTileIndex CurrentTile);

	bool AttemptedToBuild(FString &FailedMessage);

	void CancelBuild();
};
