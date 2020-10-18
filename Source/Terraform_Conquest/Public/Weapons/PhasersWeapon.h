// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Weapon.h"
#include "PhasersWeapon.generated.h"

/**
 * 
 */
UCLASS()
class TERRAFORM_CONQUEST_API APhasersWeapon : public AWeapon
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "ProjectileType", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AProjectile> ProjectileBlueprint;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	class UParticleSystem* HitEffect = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	int32 DamagePerShot;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "ProjectileSpeed", meta = (AllowPrivateAccess = "true"))
	float ProjectileSpeed = 1000.0f;

	virtual void BeginPlay() override;

	virtual void Fire() override;

	virtual void AmmoRegen() override;

public:

	APhasersWeapon();

	virtual void ChangeActiveState(const bool AmIActive) override;

	virtual void OnAttach(AActor* MyOwner, USceneComponent* OwnerMesh) override;
};
