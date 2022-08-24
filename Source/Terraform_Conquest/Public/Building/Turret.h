// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "Building/Building.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS()
class TERRAFORM_CONQUEST_API ATurret : public ABuilding
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class UTurret_Mesh* MyTurret = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class UBarrel_Mesh* MyBarrel = nullptr;

	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadWrite, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	TArray<class AWeapon*> TurretWeapons;
	UPROPERTY(EditDefaultsOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AWeapon> WeaponBlueprint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	int32 TurretGuns = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Aiming", meta = (AllowPrivateAccess = "true"))
	class UTurret_Aiming_Component* MyAimingComp = nullptr;

	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category = "Fire", meta = (AllowPrivateAccess = "true"))
	float Range = 5000.0f;

	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category = "ActiveStatus", meta = (AllowPrivateAccess = "true"))
	bool bActivated = false;

private:
	void SetUpMyStimulis();

protected:
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "AI")
	class UAIPerceptionStimuliSourceComponent* Stimulus = nullptr;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Death() override;

public:

	ATurret();

	/* Property replication */
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void Fire(AActor* Target);

	void AimAt(AActor* Target);

	bool AmILookingAtTargetDir(FVector Direction);

	void SetActiveState(bool bAmIActive);
	UFUNCTION(reliable, server, WithValidation)
		void ServerSetActiveState(bool bAmIActive);

	bool GetActiveState();
};
