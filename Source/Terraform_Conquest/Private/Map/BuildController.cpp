// Alex Chatt Terraform_Conquest 2020

#include "../../Public/Map/BuildController.h"
#include "../../Public/Map/MapController.h"
#include "../../Public/Map/MapTile.h"
#include "../../Public/Building/BuildingBluePrint/BuildingBluePrint.h"
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

	AActor* MapControllerActor = UGameplayStatics::GetActorOfClass(GetWorld(), AMapController::StaticClass());
	if (ensure(MapControllerActor))
	{
		MapController = Cast<AMapController>(MapControllerActor);
	}
}

// Called every frame
void ABuildController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABuildController::CreateBuildingBlueprint(TSubclassOf<class ABuildingBluePrint> BluePrintToSpawn)
{
	BuildingToBuild = GetWorld()->SpawnActor<ABuildingBluePrint>(BluePrintToSpawn, FVector(0,0,-100000), FRotator(0));
}

void ABuildController::SetBluePrintLocation(FVector Pos, FTileIndex CurrentTile)
{
	if (!BuildingToBuild) { return; }

	bool ChangedTile = BuildingToBuild->bHasTileImOnChanged(CurrentTile);
	if (ChangedTile)
	{
		BuildingToBuild->NewPlacement(MapController->GetTilePosFromIndex(CurrentTile), CurrentTile);
		FTileIndex PSize, NSize;
		BuildingToBuild->GetBuildingTileSize(PSize, NSize);
		TilesBuildingWillBeOn.Empty();
		BuildingToBuild->SetAreTilesAvailable(MapController->CanBuildCheck(Pos, TilesBuildingWillBeOn));
	}
}

bool ABuildController::AttemptedToBuild(FString &FailedMessage)
{ 
	if (!BuildingToBuild) { return false; }

	//Also check if we have resources to build
	//if(ResourceCheck())
	if (BuildingToBuild->BuildAttempt(TeamId, TilesBuildingWillBeOn))
	{
		//take away resources
		BuildingToBuild->Destroy();
		BuildingToBuild = nullptr;
		TilesBuildingWillBeOn.Empty();
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

void ABuildController::SetTeamID(ETeam TeamID)
{
	TeamId = TeamID;
}

ETeam ABuildController::GetTeamId() const
{
	return TeamId;
}