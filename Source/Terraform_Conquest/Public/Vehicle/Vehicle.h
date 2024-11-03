// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "Pawns/TeamActionPawn.h"
#include "Utility/TeamsEnum.h"
#include "Utility/PID_Controller.h"
#include "Vehicle.generated.h"

UCLASS()
class TERRAFORM_CONQUEST_API AVehicle : public ATeamActionPawn
{
	GENERATED_BODY()

private:

	//Replicated vars
	UPROPERTY(Replicated)
		FVector MyPosition;
	UPROPERTY(Replicated)
		FRotator MyRotation;
	UPROPERTY(Replicated)
		bool WantToFire = false;

	bool bAreLightsOn = false;

private:

	void SetUpMyStimulis();

	void ChangeWeapon();

	void DestoryMe();

	//Turn lights on for server and clients
	void ToggleLights();
	UFUNCTION(reliable, server, WithValidation)
		void ServerToggleLights(bool bLightState);
	UFUNCTION(Reliable, NetMulticast)
		void MultiToggleLights(bool bLightState);

	//Update server and clients for Vehicle transform
	void UpdateTransform();
	UFUNCTION(Unreliable, server, WithValidation)
		void ServerSetTransform(FVector NewPosition, FRotator NewRotation);

protected:
	
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Health")
		class UHealth_Component* MyHealth = nullptr;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Mesh")
		class UStaticMeshComponent* MyMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		class UCameraComponent* FPSCamera = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		class UCameraComponent* TPSCamera = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		class USpringArmComponent* TPSCameraSpring = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		bool BIs1stPersonCamera = true;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "LookControl", meta = (AllowPrivateAccess = "true"))
		float CamSense = 1.0f;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "LookControl", meta = (AllowPrivateAccess = "true"))
		float DefaultCameraRotation = 20.0f;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "WeaponController")
		class UWeapon_Controller_Component* VehicleWeaponControllerComp = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
		float AiFireAngleCutoff = 10.0f;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "MiniMapIcon")
		class UMiniMapIcon_Component* MiniMapIconComp = nullptr;

	UPROPERTY(Replicated, EditDefaultsOnly, BluePrintReadWrite, Category = "Lights")
		TArray<class URectLightComponent*> Lights;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "AI")
		class UAIPerceptionStimuliSourceComponent* Stimulus = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Death")
		float DestroyTime = 1.0f;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Name")
		FName VehicleName = "";

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetUpLights();

	//Camera change for server and other clients
	virtual void CameraChange();
	UFUNCTION(reliable, server, WithValidation)
		void ServerCameraChange(bool bIsFPSCam);
	UFUNCTION(Reliable, NetMulticast)
		void MultiCameraChange(bool bIsFPSCam);

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	virtual void Death();

public:

public:	
	// Sets default values for this pawn's properties
	AVehicle();

	/** Property replication */
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool ShouldIStartShooting(FVector TargetLocation) PURE_VIRTUAL(AVehicle::ShouldIStartShooting, return false;);

	virtual void Fire();

	virtual bool CanAimAtTarget(FVector targetpos) PURE_VIRTUAL(AVehicle::CanAimAtTarget, return false;);

	void StopFiring();
};
