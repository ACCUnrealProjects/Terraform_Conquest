// Alex Chatt Terraform_Conquest 2020

#include "Components/Hover_Move_Component.h"
#include "Components/StaticMeshComponent.h"
#include "Components/Hover_Component.h"

// Sets default values for this component's properties
UHover_Move_Component::UHover_Move_Component()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UHover_Move_Component::BeginPlay()
{
	Super::BeginPlay();

	OwnerMesh = GetOwner()->FindComponentByClass<UStaticMeshComponent>();

	if (!ensure(OwnerMesh)) { return; }
}

void UHover_Move_Component::SetTrusterSpeed(float NewForwardTrust)
{
	ForwardThrust = NewForwardTrust;
	BackWardsThrust = ForwardThrust * BackWardsThrestMulti;
	StrafeThrust = ForwardThrust * StrafeThrustMulti;
}

void UHover_Move_Component::Trusters(float Amount)
{
	if (!ensure(OwnerMesh)) { return; }

	Amount = FMath::Clamp<float>(Amount, -MaxAmount, MaxAmount);
	FVector GroundForwardVector = OwnerMesh->GetForwardVector();
	if (Amount > 0.1)
	{
		OwnerMesh->AddForce(GroundForwardVector * (ForwardThrust * Amount) * OwnerMesh->GetMass());
	}
	if (Amount < -0.1 && CurrentMoveState == HoverMovementState::Hovering)
	{
		OwnerMesh->AddForce(GroundForwardVector * (BackWardsThrust * Amount) * OwnerMesh->GetMass());
	}
}

void UHover_Move_Component::Strafe(float Amount)
{
	if (CurrentMoveState == HoverMovementState::Flying) { return; }

	Amount = FMath::Clamp<float>(Amount, -MaxAmount, MaxAmount);
	if (Amount > 0.1 || Amount < -0.1)
	{
		OwnerMesh->AddForce(OwnerMesh->GetRightVector() * (StrafeThrust * Amount) * OwnerMesh->GetMass());
	}
}

void UHover_Move_Component::YawLook(float Amount)
{
	if (!ensure(OwnerMesh)) { return; }

	Amount = FMath::Clamp<float>(Amount, -MaxAmount, MaxAmount);
	OwnerMesh->AddTorqueInDegrees((Amount * TorqueSense * DefaultTorqueForce)
		* GetOwner()->GetActorUpVector(), NAME_None, true); //Yaw
}

void UHover_Move_Component::PitchLook(float Amount)
{
	if (!ensure(OwnerMesh)) { return; }
	if (CurrentMoveState != HoverMovementState::Flying) { return; }

	Amount = FMath::Clamp<float>(Amount, -MaxAmount, MaxAmount);
	OwnerMesh->AddTorqueInDegrees(((Amount * TorqueSense * DefaultTorqueForce)
		* -1.0f) * GetOwner()->GetActorRightVector(), NAME_None, true); //Pitch
}

void UHover_Move_Component::RollLook(float Amount)
{
	if (!ensure(OwnerMesh)) { return; }
	if (CurrentMoveState != HoverMovementState::Flying) { return; }

	Amount = FMath::Clamp<float>(Amount, -MaxAmount, MaxAmount);
	OwnerMesh->AddTorqueInDegrees((Amount * TorqueSense * DefaultTorqueForce)
		* GetOwner()->GetActorForwardVector(), NAME_None, true); //Roll
}

void UHover_Move_Component::SwitchMovementMode()
{
	switch (CurrentMoveState)
	{
	case HoverMovementState::Hovering:
		CurrentMoveState = HoverMovementState::Flying;
		ForwardThrust *= ForwardThrustMulti;
		break;
	case HoverMovementState::Flying:
		CurrentMoveState = HoverMovementState::Hovering;
		ForwardThrust /= ForwardThrustMulti;
		OwnerMesh->SetEnableGravity(true);
		break;
	}
}

void UHover_Move_Component::FlightGravityToggle()
{
	//Check is speed is below certain ammount
	//If so, re-enable gravity on ship so it starts to drop
	if (GetOwner()->GetVelocity().Size() >= GravitySpeedCutoff)
	{
		OwnerMesh->SetEnableGravity(false);
	}
	else
	{
		OwnerMesh->SetEnableGravity(true);
	}
}

void UHover_Move_Component::LookAtTarget(AActor* Target)
{
	bIHaveTarget = true;
	FVector DirToTarget = (Target->GetActorLocation() - GetOwner()->GetActorLocation()).GetSafeNormal();
	float TargetYaw = DirToTarget.Rotation().Yaw;
	float CurretYaw = GetOwner()->GetActorForwardVector().GetSafeNormal().Rotation().Yaw;
	float YawChange = RotationPid.Calculate(TargetYaw, CurretYaw, GetWorld()->GetDeltaSeconds(), true);
	YawLook(YawChange);
}

void UHover_Move_Component::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// First work out the movement
	FVector AIDirection = MoveVelocity.GetSafeNormal();
	FVector MyForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector MyRight = GetOwner()->GetActorRightVector().GetSafeNormal();

	if (!bAIStrafeMovement)
	{
		FVector MoveToLocation = GetOwner()->GetActorLocation() + MoveVelocity;
		FVector MoveFactor = HoverMovementPid.Calculate(MoveToLocation, GetOwner()->GetActorLocation(), GetWorld()->GetDeltaSeconds());
		AIDirection = MoveFactor;
	}

	float ForwardMovement = FVector::DotProduct(AIDirection, MyForward);
	float SideMovement = FVector::DotProduct(AIDirection, MyRight);
	Trusters(ForwardMovement);
	Strafe(SideMovement);

	// Now work on the rotation if we want to face where we are going
	if (!bIHaveTarget)
	{
		float TargetYaw = AIDirection.Rotation().Yaw;
		float CurretYaw = MyForward.Rotation().Yaw;
		float YawChange = RotationPid.Calculate(TargetYaw, CurretYaw, GetWorld()->GetDeltaSeconds(), true);
		YawLook(YawChange);
	}
}