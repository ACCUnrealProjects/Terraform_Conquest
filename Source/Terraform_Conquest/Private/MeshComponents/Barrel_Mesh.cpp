//Alex Chatt Terraform_Conquest 2020

#include "MeshComponents/Barrel_Mesh.h"

void UBarrel_Mesh::BeginPlay()
{
	Super::BeginPlay();
	SetIsReplicated(true);
}

void UBarrel_Mesh::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Replicate everywhere
	//DOREPLIFETIME(AVehicle, MyPosition);

	//Replicate to owner client and server only

	//Replicate to none owner client and server only
}

void UBarrel_Mesh::RotateBarrel(float ElevateSpeed)
{
	float PitchChange = (FMath::Clamp<float>(ElevateSpeed, -1, +1)) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float PitchTurn = FMath::Clamp<float>(GetRelativeRotation().Pitch + PitchChange, MinTurn, MaxTurn);
	SetRelativeRotation(FRotator(PitchTurn, 0, 0));
}