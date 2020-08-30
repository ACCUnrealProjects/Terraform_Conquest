//Alex Chatt Terraform_Conquest 2020

#include "../../Public/Components/Turret_Aiming_Component.h"
#include "../../Public/MeshComponents/Barrel_Mesh.h"
#include "../../Public/MeshComponents/Turret_Mesh.h"

// Sets default values for this component's properties
UTurret_Aiming_Component::UTurret_Aiming_Component()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UTurret_Aiming_Component::BeginPlay()
{
	Super::BeginPlay();
}

void UTurret_Aiming_Component::SetUp(UTurret_Mesh* MyTurret, UBarrel_Mesh* MyBarrel)
{
	ActorTurretMesh = MyTurret;
	ActorBarrelMesh = MyBarrel;
}

void UTurret_Aiming_Component::AimToTarget(FVector TargetPosition)
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