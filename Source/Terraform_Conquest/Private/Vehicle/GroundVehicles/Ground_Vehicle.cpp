// Alex Chatt Terraform_Conquest 2020


#include "../../../Public/Vehicle/GroundVehicles/Ground_Vehicle.h"

// Sets default values
AGround_Vehicle::AGround_Vehicle()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGround_Vehicle::BeginPlay()
{
	AVehicle::BeginPlay();

}

// Called every frame
void AGround_Vehicle::Tick(float DeltaTime)
{
	AVehicle::Tick(DeltaTime);

}

void AGround_Vehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

}