// Alex Chatt Terraform_Conquest 2020

#include "Vehicle/HoverVehicles/Hover_Vehicles.h"
#include "Components/Hover_Component.h"
#include "Components/Weapon_Controller_Component.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AHover_Vehicles::AHover_Vehicles()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MainHoverComp = CreateDefaultSubobject<UHover_Component>(TEXT("MainHoverComp"));
	MainHoverComp->bEditableWhenInherited = true;
	MainHoverComp->SetupAttachment(MyMesh);

	MyMesh->SetSimulatePhysics(true);
	MyMesh->SetLinearDamping(1.0f);
	MyMesh->SetAngularDamping(1.0f);

	BIs1stPersonCamera = true;
	FPSCamera->SetActive(BIs1stPersonCamera);
	TPSCamera->SetActive(!BIs1stPersonCamera);

	TPSCameraSpring->TargetArmLength = 250.0f;
	TPSCameraSpring->SetRelativeRotation(FRotator(-20.0f, 0, 0));
	TPSCamera->SetRelativeRotation(FRotator(20.0f, 0, 0));
}

// Called when the game starts or when spawned
void AHover_Vehicles::BeginPlay()
{
	Super::BeginPlay();

	BackWardsThrust = ForwardThrust * 0.5f;
	StrafeThrust = ForwardThrust * 0.60f;
	RestrictedPitch = 0.0f;
}

// Called every frame
void AHover_Vehicles::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (CurrentMoveState)
	{
	case MovementState::Hovering:
		RotationCorrection(DeltaTime);
		break;
	case MovementState::Flying:
		FlightMovement(DeltaTime);
		break;
	}
}

void AHover_Vehicles::RotationCorrection(float DeltaTime)
{
	if (!IsLocallyControlled()) { return; }

	FRotator CurrentRotation = MyMesh->GetComponentRotation();
	// start to correct roll of ship when we are hovering
	if (MainHoverComp && MainHoverComp->AmIHovering())
	{
		FRotator GroundPitch = UKismetMathLibrary::MakeRotFromYZ(MyMesh->GetRightVector(), MainHoverComp->GetGroundNormal());
		// Lerp Towards Pitch and Roll
		// Get the Rotation for the roll on a surface, using the forward and the suface up to get the roll of the new vector (cross product again)
		FRotator GroundRoll = UKismetMathLibrary::MakeRotFromXZ(MyMesh->GetForwardVector(), MainHoverComp->GetGroundNormal());
		float WantedGroundPitch = FMath::FInterpTo(CurrentRotation.Pitch, GroundPitch.Pitch, DeltaTime, 1.0f);
		float WantedGroundRoll = FMath::FInterpTo(CurrentRotation.Roll, GroundRoll.Roll, DeltaTime, 2.0f);
		FRotator NewRotation = FRotator(WantedGroundPitch, CurrentRotation.Yaw, WantedGroundRoll);
		MyMesh->SetWorldRotation(NewRotation);
	}
	else
	{
		//If we free falling, tilt the roll of the ship to 0 and reset the roll
		float WantedGroundPitch = FMath::FInterpTo(CurrentRotation.Pitch, 0, DeltaTime, 0.75f);
		float WantedGroundRoll = FMath::FInterpTo(CurrentRotation.Roll, 0, DeltaTime, 1.25f);
		FRotator NewRotation = FRotator(WantedGroundPitch, CurrentRotation.Yaw, WantedGroundRoll);
		MyMesh->SetWorldRotation(NewRotation);
	}
}

void AHover_Vehicles::FlightMovement(float dt)
{
	if (!IsLocallyControlled()) { return; }

	//Check is speed is below certain ammount
	//If so, re-enable gravity on ship so it starts to drop
	if (GetVelocity().Size() >= GravitySpeedCutoff)
	{
		MyMesh->SetEnableGravity(false);
	}
	else
	{
		MyMesh->SetEnableGravity(true);
	}

	FRotator CameraRotation = FPSCamera->GetRelativeRotation();
	CameraRotation.Pitch = FMath::FInterpTo(CameraRotation.Pitch, 0.0f, dt, 0.1f);
	FPSCamera->SetRelativeRotation(CameraRotation);
	CameraRotation.Pitch = FMath::FInterpTo(CameraRotation.Pitch +
		-TPSCameraSpring->GetRelativeRotation().Pitch, 0.0f, dt, 0.1f);
	TPSCamera->SetRelativeRotation(CameraRotation);
}

void AHover_Vehicles::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	//Look
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AHover_Vehicles::PitchLook);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AHover_Vehicles::YawLook);
	PlayerInputComponent->BindAxis(TEXT("Roll"), this, &AHover_Vehicles::RollLook);
	//Movement
	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &AHover_Vehicles::Trusters);
	PlayerInputComponent->BindAxis(TEXT("Right"), this, &AHover_Vehicles::Strafe);
	//HoverControl
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AHover_Vehicles::IncreaseJumpHeight);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Released, this, &AHover_Vehicles::DecreaseJumpHeight);
	//Switch Movement Mode
	PlayerInputComponent->BindAction(TEXT("SwitchMode"), EInputEvent::IE_Pressed, this, &AHover_Vehicles::SwitchMovementMode);

}

void AHover_Vehicles::CameraChange()
{
	Super::CameraChange();
}

void AHover_Vehicles::ActivateHoverSystem()
{
	if (!MainHoverComp) { return; }
	MainHoverComp->ChangeHoverState(true);
	for (auto HoverComp : SupportHoverComps)
	{
		HoverComp->ChangeHoverState(true);
	}
}

void AHover_Vehicles::DeactivateHoverSystem()
{
	if (!MainHoverComp) { return; }
	MainHoverComp->ChangeHoverState(false);
	for (auto HoverComp : SupportHoverComps)
	{
		HoverComp->ChangeHoverState(false);
	}
}

void AHover_Vehicles::SwitchMovementMode()
{
	switch (CurrentMoveState)
	{
	case MovementState::Hovering:
		CurrentMoveState = MovementState::Flying;
		GetWorld()->GetTimerManager().SetTimer(HoverSwitchHandle, this, 
			&AHover_Vehicles::DeactivateHoverSystem, HoverDisengageTime, false);
		ForwardThrust *= ForwardThrustMulti;
		break;
	case MovementState::Flying:
		CurrentMoveState = MovementState::Hovering;
		ForwardThrust /= ForwardThrustMulti;
		ActivateHoverSystem();
		MyMesh->SetEnableGravity(true);
		break;
	}
}

void AHover_Vehicles::Trusters(float Amount)
{
	FVector GroundForwardVector = MyMesh->GetForwardVector();
	if (Amount > 0.1)
	{
		MyMesh->AddForce(GroundForwardVector * (ForwardThrust * Amount) * MyMesh->GetMass());
	}
	if (Amount < -0.1 && CurrentMoveState == MovementState::Hovering)
	{
		MyMesh->AddForce(GroundForwardVector * (BackWardsThrust * Amount) * MyMesh->GetMass());
	}
}

void AHover_Vehicles::Strafe(float Amount)
{
	if (!MainHoverComp || !MainHoverComp->GetbIsHoverEnabled()) { return; }

	if (Amount > 0.1 || Amount < -0.1)
	{
		MyMesh->AddForce(MyMesh->GetRightVector() * (StrafeThrust * Amount) * MyMesh->GetMass());
	}
}

void AHover_Vehicles::YawLook(float Amount)
{
	MyMesh->AddTorqueInDegrees((Amount * TorqueSense * DefaultTorqueForce) 
		* GetActorUpVector(), NAME_None, true); //Yaw
	SetWeaponRotation();
}

void AHover_Vehicles::PitchLook(float Amount)
{
	if (!GetWorld()) { return; }

	if (CurrentMoveState == MovementState::Hovering)
	{
		RestrictedPitch += (Amount * CamSense * DefaultCameraRotation)
			* GetWorld()->GetDeltaSeconds();
		RestrictedPitch = FMath::Clamp(RestrictedPitch, -HoverMaxMinPitchLook, HoverMaxMinPitchLook);
		// For hover mode, we should move the camera up and rotate the ship up/down to match the forward
		FRotator CameraRotation = FPSCamera->GetRelativeRotation();
		CameraRotation.Pitch = RestrictedPitch;
		FPSCamera->SetRelativeRotation(CameraRotation);
		CameraRotation.Pitch = RestrictedPitch + -TPSCameraSpring->GetRelativeRotation().Pitch;
		TPSCamera->SetRelativeRotation(CameraRotation);
	}
	else if (CurrentMoveState == MovementState::Flying)
	{
		MyMesh->AddTorqueInDegrees(((Amount * TorqueSense * DefaultTorqueForce)
			* -1.0f) * GetActorRightVector(), NAME_None, true); //Pitch
	}
	SetWeaponRotation();
}

void AHover_Vehicles::RollLook(float Amount)
{
	if(CurrentMoveState == MovementState::Flying)
	{
		MyMesh->AddTorqueInDegrees((Amount * TorqueSense * DefaultTorqueForce)
			* GetActorForwardVector(), NAME_None, true); //Roll
	}
}

void AHover_Vehicles::SetWeaponRotation()
{
	FVector CamPos;
	FVector CamDir;

	if (BIs1stPersonCamera && FPSCamera) {
		CamPos = FPSCamera->GetComponentLocation();
		CamDir = FPSCamera->GetForwardVector();
	}
	else if (TPSCamera) {
		CamPos = TPSCamera->GetComponentLocation();
		CamDir = TPSCamera->GetForwardVector();
	}

	VehicleWeaponControllerComp->RotateCurrentWeapons(CamPos, CamDir);
}

void AHover_Vehicles::Fire()
{
	Super::Fire();
}

void AHover_Vehicles::IncreaseJumpHeight()
{
	if (!MainHoverComp) { return; }
	MainHoverComp->IncreaseHoverHeight();
}

void AHover_Vehicles::DecreaseJumpHeight()
{
	if (!MainHoverComp) { return; }
	MainHoverComp->DecreaseHoverHeight();
}