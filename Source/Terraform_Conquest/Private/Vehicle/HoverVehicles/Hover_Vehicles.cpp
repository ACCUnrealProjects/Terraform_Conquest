// Alex Chatt Terraform_Conquest 2020

#include "Vehicle/HoverVehicles/Hover_Vehicles.h"
#include "Components/Hover_Move_Component.h"
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

	HoverMoveComp = CreateDefaultSubobject<UHover_Move_Component>(TEXT("HoverMoveComp"));
	HoverMoveComp->bEditableWhenInherited = true;

	MyMesh->SetSimulatePhysics(true);
	MyMesh->SetEnableGravity(false);
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
	if (HasAuthority())
	{
		// the owner (server) should have gravity enabled by default until an owner comes
		MyMesh->SetEnableGravity(true);
	}

	RestrictedPitch = 0.0f;
}

// Called every frame
void AHover_Vehicles::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsLocallyControlled())
	{
		switch (HoverMoveComp->GetMoveState())
		{
		case HoverMovementState::Hovering:
			RotationCorrection(DeltaTime);
			break;
		case HoverMovementState::Flying:
			FlightMovement(DeltaTime);
			break;
		}
	}
}

void AHover_Vehicles::RotationCorrection(float DeltaTime)
{
	FRotator CurrentRotation = MyMesh->GetComponentRotation();
	// start to correct roll of ship when we are hovering
	if (MainHoverComp && MainHoverComp->AmIHovering())
	{
		FRotator GroundPitch = UKismetMathLibrary::MakeRotFromYZ(MyMesh->GetRightVector(), MainHoverComp->GetGroundNormal());
		// Lerp Towards Pitch and Roll
		// Get the Rotation for the roll on a surface, using the forward and the suface up to get the roll of the new vector (cross product again)
		FRotator GroundRoll = UKismetMathLibrary::MakeRotFromXZ(MyMesh->GetForwardVector(), MainHoverComp->GetGroundNormal());
		float WantedGroundPitch = FMath::FInterpTo(CurrentRotation.Pitch, GroundPitch.Pitch, DeltaTime, PitchCorrectionSpeed);
		float WantedGroundRoll = FMath::FInterpTo(CurrentRotation.Roll, GroundRoll.Roll, DeltaTime, RollCorrectionSpeed);
		FRotator NewRotation = FRotator(WantedGroundPitch, CurrentRotation.Yaw, WantedGroundRoll);
		MyMesh->SetWorldRotation(NewRotation);
	}
	else
	{
		//If we free falling, tilt the roll of the ship to 0 and reset the roll
		float WantedGroundPitch = FMath::FInterpTo(CurrentRotation.Pitch, 0, DeltaTime, FallingPitchCorrectionSpeed);
		float WantedGroundRoll = FMath::FInterpTo(CurrentRotation.Roll, 0, DeltaTime, FallingRollCorrectionSpeed);
		FRotator NewRotation = FRotator(WantedGroundPitch, CurrentRotation.Yaw, WantedGroundRoll);
		MyMesh->SetWorldRotation(NewRotation);
	}
}

void AHover_Vehicles::FlightMovement(float dt)
{
	//Check is speed is below certain ammount
	//If so, re-enable gravity on ship so it starts to drop
	HoverMoveComp->FlightGravityToggle();

	ChangeCamerasPitch(false, dt);

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
	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &AHover_Vehicles::TrusterInput);
	PlayerInputComponent->BindAxis(TEXT("Right"), this, &AHover_Vehicles::StrafeInput);
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
	HoverMoveComp->SwitchMovementMode();

	switch (HoverMoveComp->GetMoveState())
	{
	case HoverMovementState::Flying:
		GetWorld()->GetTimerManager().SetTimer(HoverSwitchHandle, this, 
			&AHover_Vehicles::DeactivateHoverSystem, HoverDisengageTime, false);
		break;
	case HoverMovementState::Hovering:
		ActivateHoverSystem();
		break;
	}
}

void AHover_Vehicles::TrusterInput(float Amount)
{
	HoverMoveComp->Trusters(Amount);
}

void AHover_Vehicles::StrafeInput(float Amount)
{
	HoverMoveComp->Strafe(Amount);
}

void AHover_Vehicles::YawLook(float Amount)
{
	HoverMoveComp->YawLook(Amount);
	SetWeaponRotation();
}

void AHover_Vehicles::PitchLook(float Amount)
{
	if (!GetWorld()) { return; }

	if (HoverMoveComp->GetMoveState() == HoverMovementState::Hovering)
	{
		RestrictedPitch += (Amount * CamSense * DefaultCameraRotation)
			* GetWorld()->GetDeltaSeconds();
		RestrictedPitch = FMath::Clamp(RestrictedPitch, -HoverMaxMinPitchLook, HoverMaxMinPitchLook);
		// For hover mode, we should move the camera up and rotate the ship up/down to match the forward
		ChangeCamerasPitch(true, 0.0f);
	}
	else if (HoverMoveComp->GetMoveState() == HoverMovementState::Flying)
	{
		HoverMoveComp->PitchLook(Amount);
	}
	SetWeaponRotation();
}

void AHover_Vehicles::RollLook(float Amount)
{
	HoverMoveComp->RollLook(Amount);
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

	VehicleWeaponControllerComp->ServerRotateCurrentWeapons(CamPos, CamDir);
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

bool AHover_Vehicles::PitchLookAtTarget(FVector Target)
{
	if (HoverMoveComp->GetMoveState() != HoverMovementState::Hovering)
	{
		return false;
	}

	FRotator FowardRotation = GetActorForwardVector().Rotation();
	FRotator WantedRotation = (Target - FPSCamera->GetComponentLocation()).Rotation();
	float PitchOffset = WantedRotation.Pitch - FowardRotation.Pitch;
	if (PitchOffset > HoverMaxMinPitchLook || -PitchOffset < HoverMaxMinPitchLook)
	{
		return false;
	}

	RestrictedPitch = PitchOffset;
	ChangeCamerasPitch(true,0.0f);
	SetWeaponRotation();

	return true;
}


void AHover_Vehicles::ChangeCamerasPitch(bool bAmIRestricted, float dt)
{
	FRotator newFPSCameraRot = FPSCamera->GetRelativeRotation();
	FRotator newTPSCameraRot = FPSCamera->GetRelativeRotation();

	if (bAmIRestricted)
	{
		newFPSCameraRot.Pitch = RestrictedPitch;
		newTPSCameraRot.Pitch += -TPSCameraSpring->GetRelativeRotation().Pitch;
	}
	else
	{
		newFPSCameraRot.Pitch = FMath::FInterpTo(newFPSCameraRot.Pitch, 0.0f, dt, 0.1f);
		newTPSCameraRot.Pitch = FMath::FInterpTo(newTPSCameraRot.Pitch +
			-TPSCameraSpring->GetRelativeRotation().Pitch, 0.0f, dt, 0.1f);
	}

	FPSCamera->SetRelativeRotation(newFPSCameraRot);
	TPSCamera->SetRelativeRotation(newTPSCameraRot);
}

void AHover_Vehicles::Restart()
{
	Super::Restart();
	if (IsLocallyControlled())
	{
		MyMesh->SetEnableGravity(true);
	}
	else
	{
		MyMesh->SetEnableGravity(false);
	}

	if (HoverMoveComp->GetMoveState() == HoverMovementState::Hovering)
	{
		MainHoverComp->ChangeHoverState(true);
	}
}

void AHover_Vehicles::UnPossessed()
{
	Super::UnPossessed();
	if (GetWorld()->IsServer())
	{
		MyMesh->SetEnableGravity(true);
	}
	else
	{
		MyMesh->SetEnableGravity(false);
	}

	if (HoverMoveComp->GetMoveState() == HoverMovementState::Hovering)
	{
		MainHoverComp->ChangeHoverState(false);
	}
}