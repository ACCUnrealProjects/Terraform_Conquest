//Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Turret_Mesh.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TERRAFORM_CONQUEST_API UTurret_Mesh : public UStaticMeshComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly, Category = "TurretMovement", meta = (AllowPrivateAccess = "true"))
	float MaxDegreesPerSecond = 180.0f;

	UPROPERTY(EditDefaultsOnly, Category = "TurretMovement", meta = (AllowPrivateAccess = "true"))
	float MinTurn = -360.0f;

	UPROPERTY(EditDefaultsOnly, Category = "TurretMovement", meta = (AllowPrivateAccess = "true"))
	float MaxTurn = 360.0f;

protected:

public:

	void RotateTurret(float TurnSpeed);
	
};
