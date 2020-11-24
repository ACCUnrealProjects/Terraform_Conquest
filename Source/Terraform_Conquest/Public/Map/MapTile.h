// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Map/TileIndex.h"
#include "MapTile.generated.h"

UCLASS()
class TERRAFORM_CONQUEST_API AMapTile : public AActor
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TileInfo", meta = (AllowPrivateAccess = "true"))
	float TileSize = 200.0f; //cm

	float TileScale = 2.0f; //m

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileInfo", meta = (AllowPrivateAccess = "true"))
	bool Available = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileInfo", meta = (AllowPrivateAccess = "true"))
	FTileIndex MyIndex;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Landscape", meta = (AllowPrivateAccess = "true"))
	//class UStaticMeshComponent* TileMesh = nullptr;

	bool BuildAvailabilityCheck();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	AMapTile();

	void SetAvailablity(bool AmIAvailable);

	bool AmIAvailable();

	void SetIndex(int32 X, int32 Y);
};
