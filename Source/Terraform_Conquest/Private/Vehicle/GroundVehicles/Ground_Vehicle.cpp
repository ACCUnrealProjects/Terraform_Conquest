// Alex Chatt Terraform_Conquest 2020


#include "Vehicle/GroundVehicles/Ground_Vehicle.h"
#include "Camera/CameraComponent.h"

// Sets default values
AGround_Vehicle::AGround_Vehicle()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BIs1stPersonCamera = false;
	TPSCamera->SetActive(!BIs1stPersonCamera);
	FPSCamera->SetActive(BIs1stPersonCamera);
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

	RotationCorrection(DeltaTime);
}

void AGround_Vehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

}

void AGround_Vehicle::RotationCorrection(float DeltaTime)
{


}

void AGround_Vehicle::ForwardMovement(float Amount)
{

}