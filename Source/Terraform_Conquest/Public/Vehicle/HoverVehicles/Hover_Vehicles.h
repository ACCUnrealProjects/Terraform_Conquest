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
	float HoverMaxMinPitchLook = 15.0f;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	MovementState CurrentMoveState = MovementState::Hovering;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Trusters", meta = (AllowPrivateAccess = "true"))
	TArray<class UParticleSystemComponent*> TrusterEffects;

	//Time handler for Hover booster to turn off
	FTimerHandle HoverSwitchHandle;

	float RestrictedPitch = 0.0f;

private:

	//Movement and flight
	void FlightMovement(float dt);
	//Movement
	void Trusters(float Amount);
	void Strafe(float Amount);
	//Rotation
	void YawLook(float Amount);
	void PitchLook(float Amount);
	void RollLook(float Amount);
	void SetWeaponRotation();
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
	TArray<class UHover_Component*> SupportHoverComps;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	TArray<class UParticleSystemComponent*> TrusterEffect;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Movement")
	float ForwardThrust = 500.0f;
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

	//Hover Control
	void IncreaseJumpHeight();
	void DecreaseJumpHeight();

	void SwitchMovementMode();

};
