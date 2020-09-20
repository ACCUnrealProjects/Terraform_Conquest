// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponTypeEnum.h"
#include "Weapon.generated.h"

class USkeletalMeshComponent;
class USoundBase;

UCLASS()
class TERRAFORM_CONQUEST_API AWeapon : public AActor
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	USoundBase* FireSound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	USoundBase* DryClipSound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	UAnimSequence* FireAnimation = nullptr;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Name")
	FName WeaponName = "TEMPLATE";

	FCollisionQueryParams ShotParams;

	UPROPERTY(BlueprintReadOnly, Category = "WeaponType")
	GunType myWeaponType = GunType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	TArray<class UParticleSystemComponent*> FireEffect;

	UPROPERTY(BlueprintReadOnly, Category = "Ammo")
	int32 CurrentTotalAmmo;

	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
	int32 MaxAmmo;

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	int32 DamagePerShot;

	UPROPERTY(BlueprintReadOnly, Category = "Range")
	float Range;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float FireRate;

	float LastFire = -10.0f;

	AActor* GunOwner = nullptr;

	virtual void BeginPlay() override;

	virtual void Fire();

public:	

	// Sets default values for this component's properties
	AWeapon();

	void AttemptToFire();

	virtual void OnAttach(AActor* MyOwner, USceneComponent* OwnerMesh);

	virtual void ChangeActiveState(const bool AmIActive) PURE_VIRTUAL(AWeapon::ChangeActiveState, return;);

	bool OutOfAmmo() const;

	void AddAmmo(const float AmmoPercent);

	GunType GetGunType() const;
};
