//Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Barrel_Mesh.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TERRAFORM_CONQUEST_API UBarrel_Mesh : public UStaticMeshComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly, Category = "BarrelMovement", meta = (AllowPrivateAccess = "true"))
	float MaxDegreesPerSecond = 180.0f;

	UPROPERTY(EditDefaultsOnly, Category = "BarrelMovement", meta = (AllowPrivateAccess = "true"))
	float MinTurn = -10.0f;

	UPROPERTY(EditDefaultsOnly, Category = "BarrelMovement", meta = (AllowPrivateAccess = "true"))
	float MaxTurn = 40.0f;

public:
	void RotateBarrel(float ElevateSpeed);
	
};
