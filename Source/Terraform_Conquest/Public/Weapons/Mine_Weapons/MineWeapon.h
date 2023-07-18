// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Weapon.h"
#include "MineWeapon.generated.h"

/**
 * 
 */
UCLASS()
class TERRAFORM_CONQUEST_API AMineWeapon : public AWeapon
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "ProjectileType", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AMine> ProjectileBlueprint;

protected:

	virtual void BeginPlay() override;

public:
	AMineWeapon();

	virtual void FireWeapon() override;
};
