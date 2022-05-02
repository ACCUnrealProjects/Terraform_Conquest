//Alex Chatt Terraform_Conquest 2020

#include "MeshComponents/Turret_Mesh.h"

void UTurret_Mesh::BeginPlay()
{
	Super::BeginPlay();
	SetIsReplicated(true);
}

void UTurret_Mesh::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Replicate everywhere
	//DOREPLIFETIME(AVehicle, MyPosition);

	//Replicate to owner client and server only

	//Replicate to none owner client and server only
}

void UTurret_Mesh::RotateTurret(float TurnSpeed)
{
	float YawChange = (FMath::Clamp<float>(TurnSpeed, -1, +1)) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float YawTurn = FMath::Clamp<float>(GetRelativeRotation().Yaw + YawChange, MinTurn, MaxTurn);
	SetRelativeRotation(FRotator(0, YawTurn, 0));
}
