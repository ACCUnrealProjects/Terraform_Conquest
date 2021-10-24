// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "Vehicle/Vehicle.h"
#include "Hover_Vehicles.generated.h"

UENUM(BlueprintType)
enum class MovementState : uint8
{
	Flying,
	Hovering
};

UCLASS()
class TERRAFORM_CONQUEST_API AHover_Vehicles : public AVehicle
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "LookControl", meta = (AllowPrivateAccess = "true"))
	float HoverMaxMinPitchLook = 10.0f;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "LookControl", meta = (AllowPrivateAccess = "true"))
	float RotateSens = 75.0f;

	//Time handler for Hover booster to turn off
	FTimerHandle HoverSwitchHandle;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	MovementState CurrentMoveState = MovementState::Hovering;

	FVector RotationChange = FVector(0.0f);
	float RestrictedPitch = 0.0f;

	//Movement and flight
	void RotateMe();
	void FlightMovement();
	//Movement
	void Trusters(float Amount);
	void Strafe(float Amount);
	//Rotation
	void YawLook(float Amount);
	void PitchLook(float Amount);
	void RollLook(float Amount);

	// Rotation correction for hover mode
	void RotationCorrection(float DeltaTime);

	//Activate/Deactivate Hover
	UFUNCTION()
	void ActivateHoverSystem();
	void DeactivateHoverSystem();

protected:

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "HoverSetUp")
	class UHover_Component* MainHoverComp;
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "HoverSetUp")
	TArray<class UHover_Component*> AdditionalHoverComp{};

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Movement")
	float ForwardThrust = 500000.0f;
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Movement")
	float BackWardsThrust = ForwardThrust * 0.3f;
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Movement")
	float StrafeThrust = ForwardThrust * 0.50f;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Movement")
	float ForwardThrustMulti = 2.5f;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Movement")
	float HoverDisengageTime = 2.0f;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Movement")
	float GravitySpeedCutoff = 1000.0f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Sets default values for this pawn's properties
	AHover_Vehicles();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Hover Control
	void IncreaseJumpHeight();
	void DecreaseJumpHeight();

	void SwitchMovementMode();

};
