// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utility/WeaponTypeEnum.h"
#include "Utility/TeamsEnum.h"
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

private:

	void GetTeam();

	UFUNCTION(NetMulticast, UnReliable)
		void MRPC_PlaySound(FVector SoundLocation, USoundBase* Sound, bool bDontPlayForOwner);

	UFUNCTION(NetMulticast, UnReliable)
		void MRPC_PlayEffect(UParticleSystemComponent* Effect, bool bDontPlayForOwner);

protected:

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Name")
	FName WeaponName = "TEMPLATE";

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Team")
	ETeam TeamId = ETeam::Neutral;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "WeaponType")
	GunType myWeaponType = GunType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	class UParticleSystemComponent* FireEffect;

	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo")
	int32 CurrentTotalAmmo = 0;
	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo")
	int32 MaxAmmo = 0;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "AmmoRegen")
	float TimeTillAmmoRegenStarts = 15.0f;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "AmmoRegen")
	float AmmoRegenRate = 1.0f;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "AmmoRegen")
	float AmmoRegenPercentage = 1.0f;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "AmmoRegen")
	bool bCanIRegen = true;
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "AmmoRegen")
	int32 AmmoRegened = 1;
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "AmmoRegen")
	bool ExternalRegenOn = false;

	UPROPERTY(BlueprintReadOnly, Category = "Range")
	float Range = 5000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float FireRate = 1.0f;
	float LastFire = -10.0f;

	//Collision and Spawn Info for bullets/projectiles
	FActorSpawnParameters ActorParams;
	FCollisionQueryParams ShotParams;

    //Timer to regenerating Ammo
	FTimerHandle AmmoRegenTimer;
	//Timer and TimeDelegate for starting the regen process
	FTimerHandle AmmoRegenStartTimer;
	FTimerDelegate AmmoRegenStartTimerParam;

protected:

	virtual void BeginPlay() override;

	UFUNCTION(Unreliable, server, WithValidation)
	void ServerFire();

	virtual void FireWeapon(bool bClientOnlyFire) PURE_VIRTUAL(AWeapon::FireWeapon, );

	UFUNCTION()
	virtual void AmmoRegen();

public:	

	// Sets default values for this component's properties
	AWeapon();

	/** Property replication */
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void ChangeActiveState(const bool AmIActive);

	virtual void Fire();

	UFUNCTION()
	void StartRegenAmmo(const bool bExternalTrigger);

	void CancelRegenAmmo();

	void AddExternalAmmo(const float AmmoPercent);

	void AddAmmo(const int32 AmmoAmount);
	UFUNCTION(reliable, server, WithValidation)
	void ServerAddAmmo(const int32 AmmoAmount);

	float GetRange() const { return Range; }

	GunType GetGunType() const { return myWeaponType; }

	bool OutOfAmmo() const { return CurrentTotalAmmo <= 0; }

	FName GetWeaponName() const { return WeaponName; }
};
