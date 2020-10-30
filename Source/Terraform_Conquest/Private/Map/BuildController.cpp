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

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}

// Called every frame
void ABuildController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MapController && PlayerController)
	{
		if (BuildingToBuild)
		{

		}
	}
}

void ABuildController::CreateBuildingBlueprint(TSubclassOf<class ABuildingBluePrint> BluePrintToSpawn)
{
	BuildingToBuild = GetWorld()->SpawnActor<ABuildingBluePrint>(BluePrintToSpawn, FVector(0), FRotator(0));
}

bool ABuildController::AttemptedToBuild()
{
	//Also check if we have resources to build
	if (BuildingToBuild->BuildAttempt())
	{
		//take away resources
		return true;
	}
	else
	{
		//UI message "cant build here" + reason
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
