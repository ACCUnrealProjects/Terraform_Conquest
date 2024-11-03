// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "Utility/PID_Controller.h"
#include "Hover_Move_Component.generated.h"

UENUM(BlueprintType)
enum class HoverMovementState : uint8
{
	Flying,
	Hovering
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TERRAFORM_CONQUEST_API UHover_Move_Component : public UNavMovementComponent
{
	GENERATED_BODY()

private:

	const float MaxAmount = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Owner", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* OwnerMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float ForwardThrustMulti = 2.5f;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float ForwardThrust = 500.0f;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float BackWardsThrestMulti = 0.5f;
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float BackWardsThrust = ForwardThrust * BackWardsThrestMulti;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float StrafeThrustMulti = 0.75f;
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float StrafeThrust = ForwardThrust * StrafeThrustMulti;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		HoverMovementState CurrentMoveState = HoverMovementState::Hovering;
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		bool bAIStrafeMovement = false;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Rotation", meta = (AllowPrivateAccess = "true"))
		float DefaultTorqueForce = 75.0f;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Rotation", meta = (AllowPrivateAccess = "true"))
		float TorqueSense = 3.0f;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Flying", meta = (AllowPrivateAccess = "true"))
		float GravitySpeedCutoff = 1000.0f;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Target", meta = (AllowPrivateAccess = "true"))
		bool bIHaveTarget = false;

	// PID controllers for AI Rotation/Movement
	PID_Controller HoverMovementPid;
	PID_Controller RotationPid;


private:

	void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Sets default values for this component's properties
	UHover_Move_Component();

	void SetTrusterSpeed(float NewForwardTrust);

	// Movement
	void Trusters(float Amount);
	void Strafe(float Amount);
	// Rotation
	void YawLook(float Amount);
	void PitchLook(float Amount);
	void RollLook(float Amount);
	
	// Switch movement mode (hover/fly)
	void SwitchMovementMode();

	// If we are moving to slow, turn on gravity
	void FlightGravityToggle();

	// Set Straf movement for AI
	void SetAIStrafe(bool AIStrafe) { bAIStrafeMovement = AIStrafe; }

	// Vehicle Model look at a target
	void VehicleLookAtTarget(AActor *Target);
	// Reset Target
	void SetTargetLook(bool bTarget) { bIHaveTarget = bTarget; }

	void ResetPids() { HoverMovementPid.Reset(); RotationPid.Reset(); }

	HoverMovementState GetMoveState() const { return CurrentMoveState; }
};
