// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Map/TileIndex.h"
#include "BuildingBluePrint.generated.h"

UCLASS()
class TERRAFORM_CONQUEST_API ABuildingBluePrint : public AActor
{
	GENERATED_BODY()
	
private:

	FTileIndex CurretBuildTile;

	bool bAreTilesAvailable = false;

	TArray<AActor*> BlockingMeshes;

protected:

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* BuildingProtoTypeMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "OverlapSpace")
	class UBoxComponent* OverlapSpace = nullptr;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "BuildingToSpawn")
	TSubclassOf<class ABuilding> BuildingToBuild;

	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category = "BuildData")
	FTileIndex PositiveTilesFromCenter;

	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category = "BuildData")
	FTileIndex NegativeTilesFromCenter;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	ABuildingBluePrint();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void NewPlacement(FVector Pos, FTileIndex CurrentTile);

	bool BuildAttempt();

	void SetAreTilesAvailable(bool bTilesAvailable);

	void GetBuildingTileSize(FTileIndex& PosCenter, FTileIndex& NegativeCenter);

	bool bHasTileImOnChanged(FTileIndex NewCenterTile);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
