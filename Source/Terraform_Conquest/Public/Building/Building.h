// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Building.generated.h"

UCLASS()
class TERRAFORM_CONQUEST_API ABuilding : public APawn
{
	GENERATED_BODY()
	
private:	

	TArray<TSharedPtr<class Tile>> TilesImOn;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BuildingMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "OverlapSpace", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BuildOverlapSpace = nullptr;

protected:

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Health")
	class UHealth_Component* MyHealthComp = nullptr;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int32 TileWidthNeeded;
	int32 TileHeightNeeded;
	int32 CenterTile;

public:	

	// Sets default values for this actor's properties
	ABuilding();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetTilesImOn(TArray<TSharedPtr<Tile>> BuiltTiles);

	void DestroyCleanUp();

};
