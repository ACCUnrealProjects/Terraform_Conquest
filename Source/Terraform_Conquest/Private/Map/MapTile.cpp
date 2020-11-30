// Alex Chatt Terraform_Conquest 2020

#include "../../Public/Map/MapTile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMapTile::AMapTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	/*TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Mesh")));
	TileMesh->SetVisibility(false);
	TileMesh->CastShadow = false;
	TileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TileMesh->SetGenerateOverlapEvents(false);
	TileMesh->SetCanEverAffectNavigation(false);
	TileMesh->SetEnableGravity(false);
	TileMesh->bApplyImpulseOnDamage = false;
	TileMesh->bReplicatePhysicsToAutonomousProxy = false;
	SetRootComponent(TileMesh);*/
}

// Called when the game starts or when spawned
void AMapTile::BeginPlay()
{
	Super::BeginPlay();

	TileScale = TileSize / 100;
	SetActorScale3D(FVector(TileScale, TileScale, 1.0f));
	SetAvailablity(BuildAvailabilityCheck());
}

bool AMapTile::BuildAvailabilityCheck()
{
	FHitResult LandscapeRay;
	FVector RayStart = GetActorLocation();
	FVector RayEnd = RayStart + (FVector::DownVector * 2000);
	if (GetWorld()->LineTraceSingleByChannel(LandscapeRay, RayStart, RayEnd, ECollisionChannel::ECC_GameTraceChannel2))
	{
		SetActorLocation(LandscapeRay.ImpactPoint + FVector(0,0,1));
		if (LandscapeRay.ImpactNormal.Equals(FVector::UpVector, 0.1f) 
			&& LandscapeRay.ImpactPoint.Z < LandscapeRay.Actor.Get()->GetActorLocation().Z + 300
			&& LandscapeRay.ImpactPoint.Z > LandscapeRay.Actor.Get()->GetActorLocation().Z - 300)
		{
			return true;
		}
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