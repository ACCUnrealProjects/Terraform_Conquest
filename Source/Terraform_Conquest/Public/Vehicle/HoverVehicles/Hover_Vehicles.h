// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "Vehicle/Vehicle.h"
#include "Hover_Vehicles.generated.h"

UCLASS()
class TERRAFORM_CONQUEST_API AHover_Vehicles : public AVehicle
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "LookControl", meta = (AllowPrivateAccess = "true"))
	float MaxMinPitchLook = 20.0f;

	FVector RotationChange = FVector(0.0f);
	float LastPitch = 0.0f;

	//Hover Control
	void IncreaseJumpHeight();
	void DecreaseJumpHeight();
	void RotationCorrection(float DeltaTime);
	//Movement
	void Trusters(float Amount);
	void Strafe(float Amount);
	//Rotation
	void YawLook(float Amount);
	void PitchLook(float Amount);

protected:

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "HoverSetUp")
	class UHover_Component* HoverComp;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Movement")
	float ForwardThrust = 500000.0f;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Movement")
	float BackWardsThrust = ForwardThrust * 0.3f;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Movement")
	float StrafeThrust = ForwardThrust * 0.5f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Sets default values for this pawn's properties
	AHover_Vehicles();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
