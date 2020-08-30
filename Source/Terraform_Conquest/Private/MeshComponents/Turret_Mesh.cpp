//Alex Chatt Terraform_Conquest 2020

#include "../../Public/MeshComponents/Turret_Mesh.h"

void UTurret_Mesh::RotateTurret(float TurnSpeed)
{
	float YawChange = (FMath::Clamp<float>(TurnSpeed, -1, +1)) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float YawTurn = FMath::Clamp<float>(GetRelativeRotation().Yaw + YawChange, MinTurn, MaxTurn);
	SetRelativeRotation(FRotator(0, YawTurn, 0));
}
