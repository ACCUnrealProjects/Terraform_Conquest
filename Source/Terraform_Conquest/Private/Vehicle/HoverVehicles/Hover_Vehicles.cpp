// Alex Chatt Terraform_Conquest 2020


#include "../../../Public/Vehicle/HoverVehicles/Hover_Vehicles.h"
#include "../../../Public/Components/Hover_Component.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AHover_Vehicles::AHover_Vehicles()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HoverComp = CreateDefaultSubobject<UHover_Component>(TEXT("MyHoverComp"));
	HoverComp->bEditableWhenInherited = true;
	HoverComp->SetupAttachment(MyMesh);

	MyMesh->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void AHover_Vehicles::BeginPlay()
{
	AVehicle::BeginPlay();

	BackWardsThrust = ForwardThrust * 0.3f;
	StrafeThrust = ForwardThrust * 0.5f;
}

// Called every frame
void AHover_Vehicles::Tick(float DeltaTime)
{
	AVehicle::Tick(DeltaTime);

	RotationCorrection(DeltaTime);
	float OldRoll = MyMesh->GetComponentRotation().Roll;
	FQuat PitchRotation(MyMesh->GetRightVector(), FMath::DegreesToRadians(LastPitch - RotationChange.Y));
	FQuat YawRotation(MyMesh->GetUpVector(), FMath::DegreesToRadians(RotationChange.Z));
	MyMesh->SetWorldRotation((YawRotation * PitchRotation * MyMesh->GetComponentQuat()));
	MyMesh->SetWorldRotation(FRotator(MyMesh->GetComponentRotation().Pitch, MyMesh->GetComponentRotation().Yaw, OldRoll));
	LastPitch = RotationChange.Y;
	RotationChange.Z = 0.0f;
}

void AHover_Vehicles::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	//Look
	PlayerInputComponent->BindAxis("LookUp", this, &AHover_Vehicles::PitchLook);
	PlayerInputComponent->BindAxis("LookRight", this, &AHover_Vehicles::YawLook);
	//Movement
	PlayerInputComponent->BindAxis("Forward", this, &AHover_Vehicles::Trusters);
	PlayerInputComponent->BindAxis("Right", this, &AHover_Vehicles::Strafe);
	//HoverControl
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AHover_Vehicles::IncreaseJumpHeight);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &AHover_Vehicles::DecreaseJumpHeight);
	//Fire

}


void AHover_Vehicles::IncreaseJumpHeight()
{
	HoverComp->IncreaseHoverHeight();
}

void AHover_Vehicles::DecreaseJumpHeight()
{
	HoverComp->DecreaseHoverHeight();
}

void AHover_Vehicles::Trusters(float Amount)
{
	FVector GroundForwardVector = MyMesh->GetForwardVector();
	GroundForwardVector.Z = 0;
	GroundForwardVector = GroundForwardVector.GetSafeNormal();
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
	if (Amount > 0.1 || Amount < -0.1)
	{
		MyMesh->AddForce(FRotationMatrix(MyMesh->GetComponentRotation()).GetScaledAxis(EAxis::Y) * (StrafeThrust * Amount));
	}
}

void AHover_Vehicles::YawLook(float Amount)
{
	RotationChange.Z += Amount;
}

void AHover_Vehicles::PitchLook(float Amount)
{
	RotationChange.Y = FMath::Clamp(RotationChange.Y += Amount, -MaxMinPitchLook, MaxMinPitchLook);

	//IntendedChanges = Amount;
}

void AHover_Vehicles::RotationCorrection(float DeltaTime)
{
	FRotator MyRotation = MyMesh->GetComponentRotation();
	// start to correct roll of ship when we are hovering
	if (HoverComp->AmIHovering())
	{
		//HoverPitchControl(DeltaTime);

		// Lerp Towards Pitch and Roll
		// Create wanted pitch using the right and normal or the surface (think cross product for our forward vector)
		FRotator GroundPitch = UKismetMathLibrary::MakeRotFromYZ(MyMesh->GetRightVector(), HoverComp->GetGroundNormal());
		// Get the Rotation for the roll on a surface, using the forward and the suface up to get the roll of the new vector (cross product again)
		FRotator GroundRoll = UKismetMathLibrary::MakeRotFromXZ(MyMesh->GetForwardVector(), HoverComp->GetGroundNormal());
		float WantedGroundPitch = FMath::FInterpTo(MyRotation.Pitch, GroundPitch.Pitch + RotationChange.Y, DeltaTime, 1.5f);
		float WantedGroundRoll = FMath::FInterpTo(MyRotation.Roll, GroundRoll.Roll, DeltaTime, 1.5f);
		FRotator NewRotation = FRotator(WantedGroundPitch, MyRotation.Yaw, WantedGroundRoll);
		MyMesh->SetWorldRotation(NewRotation);
	}
	else
	{
		//RotationChange.Y += IntendedChanges * 0.1;

		//If we free falling, tilt the roll of the ship to 0
		float WantedGroundRoll = FMath::FInterpTo(MyRotation.Roll, 0, DeltaTime, 1.0f);
		FRotator NewRotation = FRotator(MyRotation.Pitch, MyRotation.Yaw, WantedGroundRoll);
		MyMesh->SetWorldRotation(NewRotation);
	}

}

void AHover_Vehicles::HoverPitchControl(float DeltaTime)
{
	if (RotationChange.Y > MaxMinPitchLook)
	{
		LastPitch = RotationChange.Y = FMath::FInterpTo(RotationChange.Y, MaxMinPitchLook, DeltaTime, 2.0f);
		if (RotationChange.Y + IntendedChanges < RotationChange.Y)
		{
			RotationChange.Y += IntendedChanges;
		}
	}
	else if (RotationChange.Y < -MaxMinPitchLook)
	{
		LastPitch = RotationChange.Y = FMath::FInterpTo(RotationChange.Y, -MaxMinPitchLook, DeltaTime, 2.0f);
		if (RotationChange.Y + IntendedChanges > RotationChange.Y)
		{
			RotationChange.Y += IntendedChanges;
		}
	}
	else
	{
		RotationChange.Y = FMath::Clamp(RotationChange.Y += IntendedChanges, -MaxMinPitchLook, MaxMinPitchLook);
	}
}