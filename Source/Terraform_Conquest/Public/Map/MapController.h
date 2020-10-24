// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapController.generated.h"

class AMapTile;
class Tile;

UCLASS()
class TERRAFORM_CONQUEST_API AMapController : public AActor
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapInfo", meta = (AllowPrivateAccess = "true"))
	class ALandscape* LevelLandScape = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "MapInfo", meta = (AllowPrivateAccess = "true"))
	int32 MapWidth;
	UPROPERTY(BlueprintReadOnly, Category = "MapInfo", meta = (AllowPrivateAccess = "true"))
	int32 MapHeight;

	TArray<TArray<AMapTile*>> Tiles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileData", meta = (AllowPrivateAccess = "true"))
	int32 TileSize = 200;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "TileData", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AMapTile> TileBlueprint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Sets default values for this actor's properties
	AMapController();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AttemptToBuild();

	void GetTileImLookingAt(FVector GroundPosition);

};
