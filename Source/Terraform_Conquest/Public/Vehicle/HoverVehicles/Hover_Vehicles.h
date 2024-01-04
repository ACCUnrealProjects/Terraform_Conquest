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
		float HoverMaxMinPitchLook = 15.0f;
	float RestrictedPitch = 0.0f;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "RotationCorrection", meta = (AllowPrivateAccess = "true"))
		float RollCorrectionSpeed = 2.0f;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "RotationCorrection", meta = (AllowPrivateAccess = "true"))
		float FallingRollCorrectionSpeed = 1.25f;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "RotationCorrection", meta = (AllowPrivateAccess = "true"))
		float PitchCorrectionSpeed = 1.0f;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "RotationCorrection", meta = (AllowPrivateAccess = "true"))
		float FallingPitchCorrectionSpeed = 0.75f;

	//Time handler for Hover booster to turn off
	FTimerHandle HoverSwitchHandle;

private:

	//Movement and flight
	void FlightMovement(float dt);
	//Movement
	void TrusterInput(float Amount);
	void StrafeInput(float Amount);
	//Rotation
	void YawLook(float Amount);
	void PitchLook(float Amount);
	void RollLook(float Amount);
	void SetWeaponRotation();
	// Rotation correction for hover mode
	void RotationCorrection(float DeltaTime);
	//Rotate the pitch of the Cameras
	void ChangeCamerasPitch(bool bAmIRestricted, float dt);
	//Activate/Deactivate Hover
	UFUNCTION()
	void ActivateHoverSystem();
	void DeactivateHoverSystem();

protected:

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "HoverSetUp")
		class UHover_Move_Component* HoverMoveComp = nullptr;
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "HoverSetUp")
		class UHover_Component* MainHoverComp = nullptr;
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "HoverSetUp")
		TArray<class UHover_Component*> SupportHoverComps;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
		TArray<class UParticleSystemComponent*> TrusterEffect;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "MoveSwitch")
		float HoverDisengageTime = 2.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Camera Change (FPS/TPS)
	virtual void CameraChange() override;

public:	

	// Sets default values for this pawn's properties
	AHover_Vehicles();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Fire Override
	virtual void Fire() override;

	//Camera LookAt (Pitch)
	bool PitchLookAtTarget(FVector Target);

	//Hover Control
	void IncreaseJumpHeight();
	void DecreaseJumpHeight();

	void SwitchMovementMode();
};
