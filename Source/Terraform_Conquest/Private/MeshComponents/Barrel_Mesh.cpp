//Alex Chatt Terraform_Conquest 2020

#include "../../Public/MeshComponents/Barrel_Mesh.h"

void UBarrel_Mesh::RotateBarrel(float ElevateSpeed)
{
	float PitchChange = (FMath::Clamp<float>(ElevateSpeed, -1, +1)) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float PitchTurn = FMath::Clamp<float>(GetRelativeRotation().Pitch + PitchChange, MinTurn, MaxTurn);
	SetRelativeRotation(FRotator(PitchTurn, 0, 0));
}