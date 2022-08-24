// Alex Chatt Terraform_Conquest 2020

#include "Vehicle/GroundVehicles/Ground_Vehicle.h"
#include "Components/Tracks_Move_Component.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"

// Sets default values
AGround_Vehicle::AGround_Vehicle()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GroundMovementComp = CreateDefaultSubobject<UTracks_Move_Component>(TEXT("Ground Movement Comp"));
	GroundMovementComp->bEditableWhenInherited = true;

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

}

void AGround_Vehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	//Look
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AGround_Vehicle::InputPitch);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AGround_Vehicle::InputYaw);
	//Movement
	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &AGround_Vehicle::InputForwardMovement);
	PlayerInputComponent->BindAxis(TEXT("Right"), this, &AGround_Vehicle::InputTurn);

}

void AGround_Vehicle::CameraChange()
{
	Super::CameraChange();
}

void AGround_Vehicle::InputPitch(float Amount)
{

}

void AGround_Vehicle::InputYaw(float Amount)
{

}

void AGround_Vehicle::InputForwardMovement(float Amount)
{

}

void AGround_Vehicle::InputTurn(float Amount)
{

}