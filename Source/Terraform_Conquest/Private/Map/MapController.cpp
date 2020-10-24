// Alex Chatt Terraform_Conquest 2020


#include "../../Public/Map/MapController.h"
#include "../../Public/Map/MapTile.h"
#include "Landscape.h"

// Sets default values
AMapController::AMapController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMapController::BeginPlay()
{
	Super::BeginPlay();

	//Number of components * (Section Size * section per component) * sizescale
	//(square root: Component count) * ((component res -1) * component subsections) * 100
	//Only works if heightmap is same xy res
	if (!LevelLandScape) { return; }

	int32 QuadsRes = LevelLandScape->ComponentSizeQuads;
	int32 SubSubsectionNum = LevelLandScape->NumSubsections;
	int32 CompNum = LevelLandScape->LandscapeComponents.Num();
	MapWidth = MapHeight = (FMath::Sqrt(CompNum)) * QuadsRes * SubSubsectionNum * 100;

	FVector StartingSpawnPos = LevelLandScape->GetActorLocation();
	StartingSpawnPos.X += TileSize / 2;
	StartingSpawnPos.Y += TileSize / 2;
	StartingSpawnPos.Z += 800;

	TArray<AMapTile*> WidthTiles;

	for (int i = 0; i < MapWidth; i += TileSize)
	{
		WidthTiles.Empty();
		for (int y = 0; y < MapHeight; y += TileSize)
		{
			WidthTiles.Add(GetWorld()->SpawnActor<AMapTile>(TileBlueprint, FVector(StartingSpawnPos.X + i, StartingSpawnPos.X + y, StartingSpawnPos.Z), FRotator(0)));
		}
		Tiles.Add(WidthTiles);
	}
}

// Called every frame
void AMapController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMapController::AttemptToBuild()
{

}

void AMapController::GetTileImLookingAt(FVector GroundPosition)
{
	if (Tiles.Num() < 1 || Tiles[0].Num() < 1) { return; }

	GroundPosition.X += MapWidth / 2;
	GroundPosition.Y += MapHeight / 2;

	int32 MapX = FMath::RoundToInt(GroundPosition.X / TileSize);
	int32 MapY = FMath::RoundToInt(GroundPosition.Y / TileSize);
	
	if (Tiles.IsValidIndex(MapX) && Tiles[MapX].IsValidIndex(MapY))
	{
		FVector ClosestTilePos = Tiles[MapX][MapY]->GetActorLocation();
		UE_LOG(LogTemp, Warning, TEXT("Closet Tile Pos is %s"), *ClosestTilePos.ToString());
		UE_LOG(LogTemp, Warning, TEXT("The Tile index is X: %i Y: %i"), MapX, MapY);
	}
}