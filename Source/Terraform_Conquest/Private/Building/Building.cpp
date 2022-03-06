// Alex Chatt Terraform_Conquest 2020
// https://forums.unrealengine.com/development-discussion/c-gameplay-programming/1569711-how-do-i-use-the-ai-perception-teams


#include "../../Public/Building/Building.h"
#include "../../Public/Map/MapTile.h"
#include "../../Public/Components/Health_Component.h"
#include "Components/BoxComponent.h"

// Sets default values
ABuilding::ABuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	SetRootComponent(BuildingMesh);
	BuildingMesh->bEditableWhenInherited = true;

	BuildOverlapSpace = CreateDefaultSubobject<UBoxComponent>(TEXT("Bounding Box"));
	BuildOverlapSpace->SetupAttachment(BuildingMesh);
	BuildOverlapSpace->bEditableWhenInherited = true;

	MyHealthComp = CreateDefaultSubobject<UHealth_Component>(TEXT("MyHealthComp"));
	MyHealthComp->bEditableWhenInherited = true;

}

// Called when the game starts or when spawned
void ABuilding::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABuilding::SetTilesImOn(TArray<AMapTile*> BuiltTiles)
{
	TilesImOn = BuiltTiles;
}

void ABuilding::SetTeamID(FGenericTeamId TeamID)
{
	TeamId = TeamID;
}

FGenericTeamId ABuilding::GetTeamId() const
{
	return TeamId;
}

void ABuilding::StartDestroy()
{
	
}

void ABuilding::DestroyCleanUp()
{
	for (int32 i = 0; i < TilesImOn.Num(); i++)
	{
		TilesImOn[i]->SetAvailablity(true);
	}
}