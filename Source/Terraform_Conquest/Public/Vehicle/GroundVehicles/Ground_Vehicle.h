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

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "LookControl", meta = (AllowPrivateAccess = "true"))
	float MaxMinPitchLook = 30.0f;

private:
	//Rotation
	void Rotation(float DeltaTime);
	//Movement
	void ForwardMovement(float Amount);

protected:

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Movement")
	float ForwardThrust = 500000.0f;
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Movement")
	float BackWardsThrust = ForwardThrust * 0.3f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Camera Change (FPS/TPS)
	virtual void CameraChange() override;

public:

	// Sets default values for this pawn's properties
	AGround_Vehicle();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
