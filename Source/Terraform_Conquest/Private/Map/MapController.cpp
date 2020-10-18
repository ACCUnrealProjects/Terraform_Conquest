// Alex Chatt Terraform_Conquest 2020


#include "../../Public/Map/MapController.h"

// Sets default values
AMapController::AMapController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMapController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMapController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

