// Alex Chatt Terraform_Conquest 2020

#include "../../Public/Map/BuildController.h"
#include "../../Public/Map/MapController.h"
#include "../../Public/Building/BuildingBluePrint.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABuildController::ABuildController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ABuildController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABuildController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABuildController::CreateBuildingBlueprint(TSubclassOf<class ABuildingBluePrint> BluePrintToSpawn)
{
	BuildingToBuild = GetWorld()->SpawnActor<ABuildingBluePrint>(BluePrintToSpawn, FVector(0), FRotator(0));
}

void ABuildController::SetBluePrintLocation(FVector Pos, FTileIndex CurrentTile)
{
	if (!BuildingToBuild) { return; }

	bool ChangedTile = BuildingToBuild->bHasTileImOnChanged(CurrentTile);
	BuildingToBuild->NewPlacement(Pos, CurrentTile);
	FTileIndex PSize, NSize;
	BuildingToBuild->GetBuildingTileSize(PSize, NSize);
	if (ChangedTile)
	{
		BuildingToBuild->SetAreTilesAvailable(MapController->CanBuildCheck(PSize, NSize, Pos));
	}
}

bool ABuildController::AttemptedToBuild(FString &FailedMessage)
{
	//Also check if we have resources to build
	//if(ResourceCheck())
	if (BuildingToBuild->BuildAttempt())
	{
		//take away resources
		return true;
	}
	else
	{
		//UI message "cant build here" to FailedMessage
		FailedMessage = "Can not be build here";
	}

	return false;
}


void ABuildController::CancelBuild()
{
	if (BuildingToBuild)
	{
		BuildingToBuild->Destroy();
	}

	BuildingToBuild = nullptr;
}
