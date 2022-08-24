// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Weapon.h"
#include "MorterWeapon.generated.h"

/**
 * 
 */
UCLASS()
class TERRAFORM_CONQUEST_API AMorterWeapon : public AWeapon
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "ProjectileType", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class AMorter_Projectile> ProjectileBlueprint;

protected:

	virtual void BeginPlay() override;

public:

	AMorterWeapon();

	virtual void FireWeapon() override;
};
