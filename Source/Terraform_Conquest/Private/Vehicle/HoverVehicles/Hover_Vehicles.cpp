// Alex Chatt Terraform_Conquest 2020


#include "../../../Public/Vehicle/HoverVehicles/Hover_Vehicles.h"
#include "../../../Public/Components/Hover_Component.h"
#include "../../../Public/Components/Master_Hover_Component.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"

// Sets default values
AHover_Vehicles::AHover_Vehicles()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MainHoverComp = CreateDefaultSubobject<UMaster_Hover_Component>(TEXT("MainHoverComp"));
	MainHoverComp->bEditableWhenInherited = true;
	MainHoverComp->SetupAttachment(MyMesh);

	MyMesh->SetSimulatePhysics(true);

	BIs1stPersonCamera = true;
	FPSCamera->SetActive(BIs1stPersonCamera);
	TPSCamera->SetActive(!BIs1stPersonCamera);
}

// Called when the game starts or when spawned
void AHover_Vehicles::BeginPlay()
{
	AVehicle::BeginPlay();

	BackWardsThrust = ForwardThrust * 0.3f;
	StrafeThrust = ForwardThrust * 0.60f;
	RestrictedPitch = 0.0f;
}

// Called every frame
void AHover_Vehicles::Tick(float DeltaTime)
{
	AVehicle::Tick(DeltaTime);

	switch (CurrentMoveState)
	{
	case MovementState::Hovering:
		RotationCorrection(DeltaTime);
		break;
	case MovementState::Flying:

		break;
	}
	RotateMe();
}

void AHover_Vehicles::RotateMe()
{
	float OldRoll = MyMesh->GetComponentRotation().Roll;
	MyMesh->AddTorqueInDegrees(RotationChange.Y * GetActorRightVector(), NAME_None, true); //Pitch
	MyMesh->AddTorqueInDegrees(RotationChange.Z * GetActorUpVector(), NAME_None, true); //Yaw
	MyMesh->AddTorqueInDegrees(RotationChange.X * GetActorForwardVector(), NAME_None, true); //Roll
	FRotator GroundPitch = FRotator::ZeroRotator;
	if (CurrentMoveState == MovementState::Hovering && MainHoverComp->AmIHovering())
	{
		// Create wanted pitch using the right and normal or the surface (think cross product for our forward vector)
		GroundPitch = UKismetMathLibrary::MakeRotFromYZ(MyMesh->GetRightVector(), MainHoverComp->GetGroundNormal());
		// Maybe the best thing to do here is just reverse the AddTorqueInDegrees if the Current Pitch 
		// of the ship is over/under the angle ammount
		MyMesh->SetWorldRotation(FRotator(MyMesh->GetComponentRotation().Pitch, MyMesh->GetComponentRotation().Yaw, OldRoll));
	}
	RestrictedPitch = FMath::Clamp(MyMesh->GetComponentRotation().Pitch, GroundPitch.Pitch - HoverMaxMinPitchLook, GroundPitch.Pitch + HoverMaxMinPitchLook);
	RotationChange = FVector::ZeroVector;
}

void AHover_Vehicles::RotationCorrection(float DeltaTime)
{
	FRotator MyRotation = MyMesh->GetComponentRotation();
	// start to correct roll of ship when we are hovering
	if (MainHoverComp->AmIHovering())
	{
		// Lerp Towards Pitch and Roll
		// Get the Rotation for the roll on a surface, using the forward and the suface up to get the roll of the new vector (cross product again)
		FRotator GroundRoll = UKismetMathLibrary::MakeRotFromXZ(MyMesh->GetForwardVector(), MainHoverComp->GetGroundNormal());
		float WantedGroundPitch = FMath::FInterpTo(MyRotation.Pitch, RestrictedPitch, DeltaTime, 1.0f);
		float WantedGroundRoll = FMath::FInterpTo(MyRotation.Roll, GroundRoll.Roll, DeltaTime, 1.0f);
		FRotator NewRotation = FRotator(WantedGroundPitch, MyRotation.Yaw, WantedGroundRoll);
		MyMesh->SetWorldRotation(NewRotation);
	}
	else
	{
		//If we free falling, tilt the roll of the ship to 0 and reset the roll
		//float WantedGroundPitch = FMath::FInterpTo(MyRotation.Pitch, 0 + RotationChange.Y, DeltaTime, 0.75f);
		float WantedGroundRoll = FMath::FInterpTo(MyRotation.Roll, 0, DeltaTime, 1.25f);
		FRotator NewRotation = FRotator(MyRotation.Pitch, MyRotation.Yaw, WantedGroundRoll);
		MyMesh->SetWorldRotation(NewRotation);
	}

}


void AHover_Vehicles::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	//Look
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AHover_Vehicles::PitchLook);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AHover_Vehicles::YawLook);
	//Movement
	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &AHover_Vehicles::Trusters);
	PlayerInputComponent->BindAxis(TEXT("Right"), this, &AHover_Vehicles::Strafe);
	//HoverControl
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AHover_Vehicles::IncreaseJumpHeight);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Released, this, &AHover_Vehicles::DecreaseJumpHeight);
	//Switch Movement Mode
	PlayerInputComponent->BindAction(TEXT("SwitchMode"), EInputEvent::IE_Pressed, this, &AHover_Vehicles::SwitchMovementMode);
}


void AHover_Vehicles::IncreaseJumpHeight()
{
	MainHoverComp->IncreaseHoverHeight();
}

void AHover_Vehicles::DecreaseJumpHeight()
{
	MainHoverComp->DecreaseHoverHeight();
}

void AHover_Vehicles::ChangeHoverSystem(bool bShouldIHover)
{
	MainHoverComp->ChangeHoverState(bShouldIHover);
	for (auto HoverComp : AdditionalHoverComp)
	{
		HoverComp->ChangeHoverState(bShouldIHover);
	}
}

void AHover_Vehicles::SwitchMovementMode()
{
	switch (CurrentMoveState)
	{
	case MovementState::Hovering:
		CurrentMoveState = MovementState::Flying;
		MainHoverComp->ChangeHoverState(false);
		ForwardThrust *= ForwardThrustMulti;
		break;
	case MovementState::Flying:
		CurrentMoveState = MovementState::Hovering;
		ForwardThrust /= ForwardThrustMulti;
		MyMesh->SetEnableGravity(true);
		break;
	}
}

void AHover_Vehicles::Trusters(float Amount)
{
	if (!MainHoverComp->GetbIsHoverEnabled()) { return; }

	FVector GroundForwardVector = MyMesh->GetForwardVector();
	if (Amount > 0.1)
	{
		MyMesh->AddForce(GroundForwardVector * (ForwardThrust * Amount));
	}
	if (Amount < -0.1)
	{
		MyMesh->AddForce(GroundForwardVector * (BackWardsThrust * Amount));
	}
}

void AHover_Vehicles::Strafe(float Amount)
{
	if (!MainHoverComp->GetbIsHoverEnabled()) { return; }

	if (Amount > 0.1 || Amount < -0.1)
	{
		MyMesh->AddForce(MyMesh->GetRightVector() * (StrafeThrust * Amount));
	}
}

void AHover_Vehicles::YawLook(float Amount)
{
	RotationChange.Z += Amount * RotateSens;
}

void AHover_Vehicles::PitchLook(float Amount)
{
	RotationChange.Y += (Amount * RotateSens) * -1.0f;
}

void AHover_Vehicles::RollLook(float Amount)
{
	if(CurrentMoveState == MovementState::Flying)
	{
		RotationChange.X += Amount * RotateSens;
	}
}