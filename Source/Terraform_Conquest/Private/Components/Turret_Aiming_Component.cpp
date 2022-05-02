//Alex Chatt Terraform_Conquest 2020

#include "Components/Turret_Aiming_Component.h"
#include "MeshComponents/Barrel_Mesh.h"
#include "MeshComponents/Turret_Mesh.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UTurret_Aiming_Component::UTurret_Aiming_Component()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UTurret_Aiming_Component::BeginPlay()
{
	Super::BeginPlay();
	SetIsReplicated(true);
}

void UTurret_Aiming_Component::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Replicate everywhere
	DOREPLIFETIME(UTurret_Aiming_Component, DegreesCloseToShot);
	DOREPLIFETIME(UTurret_Aiming_Component, ActorTurretMesh);
	DOREPLIFETIME(UTurret_Aiming_Component, ActorBarrelMesh);

	//Replicate to owner client and server only

	//Replicate to none owner client and server only
}

void UTurret_Aiming_Component::SetUp(UTurret_Mesh* MyTurret, UBarrel_Mesh* MyBarrel)
{
	if (GetOwner()->HasAuthority())
	{
		ActorTurretMesh = MyTurret;
		ActorBarrelMesh = MyBarrel;
	}
}

void UTurret_Aiming_Component::AimToTarget(FVector TargetPosition)
{
	ServerAimToTarget(TargetPosition);
}

bool UTurret_Aiming_Component::ServerAimToTarget_Validate(FVector TargetPosition)
{
	return false;
}

void UTurret_Aiming_Component::ServerAimToTarget_Implementation(FVector TargetPosition)
{
	if (!ActorTurretMesh || !ActorBarrelMesh) { return; }

	FVector ToTarget = TargetPosition - ActorBarrelMesh->GetComponentLocation();
	ToTarget = ToTarget.GetSafeNormal();
	FRotator DirectionRotation = ToTarget.Rotation();
	FRotator DesiredChange = DirectionRotation - ActorBarrelMesh->GetForwardVector().Rotation();
	ActorBarrelMesh->RotateBarrel(DesiredChange.Pitch);
	if (DesiredChange.Yaw > 180)
	{
		DesiredChange.Yaw = DesiredChange.Yaw - 360;
	}
	else if (DesiredChange.Yaw < -180)
	{
		DesiredChange.Yaw = DesiredChange.Yaw + 360;
	}
	ActorTurretMesh->RotateTurret(DesiredChange.Yaw);
}

bool UTurret_Aiming_Component::CloseToHittingTarget(FVector TargetPosition)
{
	if (!ActorTurretMesh || !ActorBarrelMesh) { return false; }

	FVector ToTarget = TargetPosition - ActorTurretMesh->GetComponentLocation();
	ToTarget = ToTarget.GetSafeNormal();

	if (ToTarget.Equals(ActorBarrelMesh->GetForwardVector(), 0.2f))
	{
		return true;
	}

	return false;
}
