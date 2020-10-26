// Alex Chatt Terraform_Conquest 2020

#include "../../Public/Map/MapTile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMapTile::AMapTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Mesh")));
	//SetRootComponent(TileMesh);
}

// Called when the game starts or when spawned
void AMapTile::BeginPlay()
{
	Super::BeginPlay();

	TileScale = TileSize / 100;
	SetActorScale3D(FVector(TileScale, TileScale, 1.0f));
	Available = BuildAvailabilityCheck();
}

bool AMapTile::BuildAvailabilityCheck()
{
	FHitResult LandscapeRay;
	FVector RayStart = GetActorLocation();
	FVector RayEnd = RayStart + (FVector::DownVector * 1000);
	if (GetWorld()->LineTraceSingleByChannel(LandscapeRay, RayStart, RayEnd, ECollisionChannel::ECC_GameTraceChannel2))
	{
		SetActorLocation(LandscapeRay.ImpactPoint);
		if (LandscapeRay.ImpactNormal.Equals(FVector::UpVector, 0.1f))
		{
			return true;
		}
		return false;
	}
	return false;
}

void AMapTile::SetAvailablity(bool AmIAvailable)
{
	Available = AmIAvailable;
}

bool AMapTile::AmIAvailable()
{
	return Available;
}

void AMapTile::SetIndex(int32 X, int32 Y)
{
	MyIndex.XIndex = X;
	MyIndex.YIndex = Y;
}