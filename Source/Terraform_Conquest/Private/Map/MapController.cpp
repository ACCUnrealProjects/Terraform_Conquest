// Alex Chatt Terraform_Conquest 2020

#include "../../Public/Map/MapController.h"
#include "../../Public/Map/MapTile.h"
#include "Landscape.h"

// Sets default values
AMapController::AMapController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
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
	StartingSpawnPos.Z += 1000;

	TArray<AMapTile*> WidthTiles;

	for (int x = 0; x < MapWidth; x += TileSize)
	{
		WidthTiles.Empty();
		for (int y = 0; y < MapHeight; y += TileSize)
		{
			AMapTile* NewTile = GetWorld()->SpawnActor<AMapTile>(TileBlueprint, FVector(FVector(StartingSpawnPos.X + x, StartingSpawnPos.Y + y, StartingSpawnPos.Z)), FRotator(0));
			NewTile->SetIndex(x, y);
			WidthTiles.Add(NewTile);
		}
		Tiles.Add(WidthTiles);
	}
}

// Called every frame
void AMapController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AMapController::CanBuildCheck(FVector Pos, TArray<AMapTile*> &TilesCheck)
{
	FTileIndex CenterTile = GetTileIndexFromPos(Pos);

	if (Tiles[CenterTile.XIndex][CenterTile.YIndex]->AmIAvailable() &&
		CenterTile.XIndex != -1 && CenterTile.YIndex != -1)
	{
		return true;
	}

	return false;
}

FVector AMapController::GetTilePosFromIndex(FTileIndex TileIndex)
{
	if (Tiles.IsValidIndex(TileIndex.XIndex) || !Tiles[TileIndex.XIndex].IsValidIndex(TileIndex.YIndex))
	{
		return Tiles[TileIndex.XIndex][TileIndex.YIndex]->GetActorLocation();
	}
	return FVector(0, 0, -100000);
}

FTileIndex AMapController::GetTileImLookingAt(FVector GroundPosition)
{
	if (Tiles.Num() < 1 || Tiles[0].Num() < 1) { return FTileIndex(); }
	return GetTileIndexFromPos(GroundPosition);
}

FTileIndex AMapController::GetTileIndexFromPos(FVector GroundPosition)
{
	GroundPosition.X += MapWidth / 2;
	GroundPosition.Y += MapHeight / 2;

	FTileIndex TilesIndex;
	TilesIndex.XIndex = FMath::RoundToInt(GroundPosition.X / TileSize);
	TilesIndex.YIndex = FMath::RoundToInt(GroundPosition.Y / TileSize);

	if(!Tiles.IsValidIndex(TilesIndex.XIndex) || !Tiles[TilesIndex.XIndex].IsValidIndex(TilesIndex.YIndex))
	{
		TilesIndex.XIndex = -1;
		TilesIndex.YIndex = -1;
	}

	return TilesIndex;
}