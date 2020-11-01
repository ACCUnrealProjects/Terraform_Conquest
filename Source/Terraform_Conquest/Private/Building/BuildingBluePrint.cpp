// Alex Chatt Terraform_Conquest 2020

#include "../../Public/Building/BuildingBluePrint.h"
#include "../../Public/Map/MapTile.h"
#include "Components/BoxComponent.h"

// Sets default values
ABuildingBluePrint::ABuildingBluePrint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BuildingProtoTypeMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Prototype Mesh")));

	OverlapSpace = CreateDefaultSubobject<UBoxComponent>(FName(TEXT("Bounding Box")));
}

// Called when the game starts or when spawned
void ABuildingBluePrint::BeginPlay()
{
	Super::BeginPlay();

	OverlapSpace->OnComponentBeginOverlap.AddDynamic(this, &ABuildingBluePrint::OnOverlapBegin);
	OverlapSpace->OnComponentEndOverlap.AddDynamic(this, &ABuildingBluePrint::OnOverlapEnd);
}

// Called every frame
void ABuildingBluePrint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABuildingBluePrint::NewPlacement(FVector Pos, FTileIndex CurrentTile)
{
	SetActorLocation(Pos);
	CurretBuildTile = CurrentTile;
	bAreTilesAvailable = true;
}

void ABuildingBluePrint::SetAreTilesAvailable(bool bTilesAvailable)
{
	bAreTilesAvailable = bTilesAvailable;
}

bool ABuildingBluePrint::BuildAttempt()
{
	if (!bAreTilesAvailable || BlockingMeshes.Num() > 0)
	{ 
		return false;
	}

	return true;
}

void ABuildingBluePrint::GetBuildingTileSize(FTileIndex& PosCenter, FTileIndex& NegativeCenter)
{
	PosCenter = PositiveTilesFromCenter;
	NegativeCenter = NegativeTilesFromCenter;
}

bool ABuildingBluePrint::bHasTileImOnChanged(FTileIndex NewCenterTile)
{
	if ((NewCenterTile.XIndex == CurretBuildTile.XIndex) && (NewCenterTile.YIndex == CurretBuildTile.YIndex))
	{
		return false;
	}

	return true;
}

void ABuildingBluePrint::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if other object is a building (or other mesh object), if so, add to list
	BlockingMeshes.Add(OtherActor);
}

void ABuildingBluePrint::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Check if other object is a building (or other mesh object), if so, add to list
	BlockingMeshes.Remove(OtherActor);
}