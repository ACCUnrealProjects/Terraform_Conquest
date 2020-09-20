// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "Vehicle/Vehicle.h"
#include "Ground_Vehicle.generated.h"

/**
 * 
 */
UCLASS()
class TERRAFORM_CONQUEST_API AGround_Vehicle : public AVehicle
{
	GENERATED_BODY()

private:

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Sets default values for this pawn's properties
	AGround_Vehicle();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
