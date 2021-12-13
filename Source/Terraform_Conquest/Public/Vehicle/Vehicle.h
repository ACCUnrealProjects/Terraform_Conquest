// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TeamsEnum.h"
#include "Vehicle.generated.h"

UCLASS()
class TERRAFORM_CONQUEST_API AVehicle : public APawn
{
	GENERATED_BODY()

private:

	ETeam TeamId = ETeam::None;

	bool WantToFire = false;

	bool bAreLightsOn = false;

private:

	void ChangeWeapon();

	void DestoryMe();

	void ToggleLights();

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

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "WeaponController")
	class UWeapon_Controller_Component* VehicleWeaponControllerComp = nullptr;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Lights")
	TArray<class URectLightComponent*> Lights;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Death")
	float DestroyTime = 1.0f;

	FVector FireDir;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Name")
	FName VehicleName = "";

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void CameraChange();

	// Things to change on Camera Change
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "UI")
	void CameraChangeActions(bool bChangetoFPSCam);

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	virtual void Death();

public:

public:	
	// Sets default values for this pawn's properties
	AVehicle();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetTeamID(ETeam TeamID);

	virtual void Fire();

	void StopFiring();

	ETeam GetTeamId() const { return TeamId; }

};
