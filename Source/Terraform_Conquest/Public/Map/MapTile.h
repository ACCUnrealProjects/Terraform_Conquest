// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapTile.generated.h"

UCLASS()
class TERRAFORM_CONQUEST_API AMapTile : public AActor
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TileInfo", meta = (AllowPrivateAccess = "true"))
	float TileSize = 1.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TileInfo", meta = (AllowPrivateAccess = "true"))
	float DefaultTileScale = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileInfo", meta = (AllowPrivateAccess = "true"))
	bool Available = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Landscape", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* TileMesh = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	AMapTile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};