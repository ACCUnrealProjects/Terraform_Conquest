// Alex Chatt Terraform_Conquest 2020

#include "Vehicle/GroundVehicles/Ground_Vehicle.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
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
	Super::BeginPlay();

}

// Called every frame
void AGround_Vehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Rotation(DeltaTime);
}

void AGround_Vehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

}

void AGround_Vehicle::CameraChange()
{
	Super::CameraChange();
}

void AGround_Vehicle::Rotation(float DeltaTime)
{


}

void AGround_Vehicle::ForwardMovement(float Amount)
{

}