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
		
protected:

	virtual void BeginPlay() override;

public:
	ACannonWeapon();

	virtual void FireWeapon(bool bClientOnlyFire) override;
};
