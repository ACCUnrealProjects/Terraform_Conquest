// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Weapon.h"
#include "CannonWeapon.generated.h"

/**
 * 
 */
UCLASS()
class TERRAFORM_CONQUEST_API ACannonWeapon : public AWeapon
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "ProjectileType", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ACannon_Projectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "ProjectileSpeed", meta = (AllowPrivateAccess = "true"))
	float ProjectileSpeed = 1000.0f;
			
protected:

	virtual void BeginPlay() override;

	virtual void Fire() override;

	virtual void AmmoRegen() override;

public:

	ACannonWeapon();

	virtual void ChangeActiveState(const bool AmIActive) override;

	virtual void OnAttach(AActor* MyOwner, USceneComponent* OwnerMesh) override;
	
};
