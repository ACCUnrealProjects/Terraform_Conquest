// Alex Chatt Terraform_Conquest 2020

#include "Vehicle/Vehicle.h"
#include "Components/Health_Component.h"
#include "Components/Weapon_Controller_Component.h"
#include "Components/RectLightComponent.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AVehicle::AVehicle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	SetRootComponent(MyMesh);

	MyHealth = CreateDefaultSubobject<UHealth_Component>(TEXT("MyHealthComp"));
	MyHealth->bEditableWhenInherited = true;

	FPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyFPSCam"));
	FPSCamera->bUsePawnControlRotation = false;
	FPSCamera->SetupAttachment(MyMesh);

	TPSCameraSpring = CreateDefaultSubobject<USpringArmComponent>(TEXT("TPSCamSpring"));
	TPSCameraSpring->bUsePawnControlRotation = false;
	TPSCameraSpring->bEnableCameraLag = true;
	TPSCameraSpring->bEnableCameraRotationLag = true;
	TPSCameraSpring->SetupAttachment(MyMesh);

	TPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyTPSCam"));
	TPSCamera->bUsePawnControlRotation = false;
	TPSCamera->SetupAttachment(TPSCameraSpring);

	VehicleWeaponControllerComp = CreateDefaultSubobject<UWeapon_Controller_Component>(TEXT("VehicleWeaponSystem"));
	VehicleWeaponControllerComp->bEditableWhenInherited = true;

	Tags.Add("Vehicle");
}


// Called when the game starts or when spawned
void AVehicle::BeginPlay()
{
	Super::BeginPlay();
	MyMesh->SetCenterOfMass(FVector(0, 0, -100));

	MyHealth->IHaveDied.AddUniqueDynamic(this, &AVehicle::Death);
}

// Called every frame
void AVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (WantToFire)
	{
		VehicleWeaponControllerComp->FireCurrent();
	}
}

void AVehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	//Change Camera
	PlayerInputComponent->BindAction(TEXT("Change_Camera"), EInputEvent::IE_Released, this, &AVehicle::CameraChange);
	//Weapon System
	PlayerInputComponent->BindAction(TEXT("LeftClickAction"), EInputEvent::IE_Pressed, this, &AVehicle::Fire);
	PlayerInputComponent->BindAction(TEXT("LeftClickAction"), EInputEvent::IE_Released, this, &AVehicle::StopFiring);
	PlayerInputComponent->BindAction(TEXT("RightClickAction"), EInputEvent::IE_Pressed, this, &AVehicle::ChangeWeapon);
	//Lights
	PlayerInputComponent->BindAction(TEXT("Lights"), EInputEvent::IE_Pressed, this, &AVehicle::ToggleLights);
}

void AVehicle::SetTeamID(ETeam TeamID)
{
	TeamId = TeamID;
	Tags.Add(FName(GetTeamName(TeamID)));
}

void AVehicle::CameraChange()
{
	BIs1stPersonCamera = !BIs1stPersonCamera;
	FPSCamera->SetActive(BIs1stPersonCamera);
	TPSCamera->SetActive(!BIs1stPersonCamera);
}

void AVehicle::Fire()
{
	WantToFire = true;
}

void AVehicle::StopFiring()
{
	WantToFire = false;
}

void AVehicle::ChangeWeapon()
{
	VehicleWeaponControllerComp->SwitchWeapon();
}

float AVehicle::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (MyHealth) { return MyHealth->TakeDamage(DamageAmount); }
	else { return DamageAmount; }
}

void AVehicle::Death()
{
	FTimerHandle DeathTimer;
	MyMesh->SetCenterOfMass(FVector(0, 0, 0));
	GetWorld()->GetTimerManager().SetTimer(DeathTimer, this, &AVehicle::DestoryMe, DestroyTime, false);
}

void AVehicle::DestoryMe()
{
	Destroy();
}

void AVehicle::ToggleLights()
{
	bAreLightsOn = !bAreLightsOn;

	for (auto Light : Lights)
	{
		Light->SetVisibility(bAreLightsOn);
	}
}
