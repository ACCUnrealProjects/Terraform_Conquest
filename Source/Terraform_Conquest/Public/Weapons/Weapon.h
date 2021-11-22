// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponTypeEnum.h"
#include "Weapon.generated.h"

class USoundBase;

UCLASS()
class TERRAFORM_CONQUEST_API AWeapon : public AActor
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene", meta = (AllowPrivateAccess = "true"))
	USceneComponent* WeaponSC = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	USoundBase* FireSound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	USoundBase* DryClipSound = nullptr;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Name")
	FName WeaponName = "TEMPLATE";

	UPROPERTY(BlueprintReadOnly, Category = "WeaponType")
	GunType myWeaponType = GunType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	class UParticleSystemComponent* FireEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo")
	int32 CurrentTotalAmmo;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo")
	int32 MaxAmmo;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "AmmoRegen")
	float AmmoRegenRate = 3.0f;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "AmmoRegen")
	int AmmoRegened = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float FireRate;

	FActorSpawnParameters ActorParams;

	FCollisionQueryParams ShotParams;

	FTimerHandle AmmoRegenTimer;

	float LastFire = -10.0f;

	bool ExternalRegenOn = false;

protected:

	virtual void BeginPlay() override;

	virtual void Fire();

	UFUNCTION()
	virtual void AmmoRegen();

public:	

	// Sets default values for this component's properties
	AWeapon();

	void AttemptToFire();

	virtual void ChangeActiveState(const bool AmIActive) PURE_VIRTUAL(AWeapon::ChangeActiveState, return;);

	void ExternalRegenAmmo();

	void CancelRegenAmmo();

	bool OutOfAmmo() const;

	void AddAmmo(const float AmmoPercent);

	GunType GetGunType() const;

	FName GetWeaponName() const;
};
