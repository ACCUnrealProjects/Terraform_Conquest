// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapController.generated.h"

UCLASS()
class TERRAFORM_CONQUEST_API AMapController : public AActor
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Landscape", meta = (AllowPrivateAccess = "true"))
	class ALandscape* LevelLandScape = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Landscape", meta = (AllowPrivateAccess = "true"))
	float MapWidth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Landscape", meta = (AllowPrivateAccess = "true"))
	float MapHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileMap", meta = (AllowPrivateAccess = "true"))
	float TileSize;

	TArray<TArray<class AMapTile*>> TileMap;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Sets default values for this actor's properties
	AMapController();

	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
