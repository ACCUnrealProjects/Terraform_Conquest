// Alex Chatt Terraform_Conquest 2020


#include "../../Public/Building/Building.h"
#include "../../Public/Map/MapTile.h"

// Sets default values
ABuilding::ABuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

void ABuilding::SetTilesImOn(TArray<TSharedPtr<Tile>> BuiltTiles)
{
	TilesImOn = BuiltTiles;
}

void ABuilding::DestroyCleanUp()
{
	for (int i = 0; i < TilesImOn.Num(); i++)
	{
		//TilesImOn[i]->SetAvailablity(true);
	}
}