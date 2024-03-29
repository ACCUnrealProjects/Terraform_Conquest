// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Weapon.h"
#include "MachineGun.generated.h"

/**
 * 
 */
UCLASS()
class TERRAFORM_CONQUEST_API AMachineGun : public AWeapon
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "ProjectileType", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class ATracer_Round> ProjectileBlueprint;

protected:

	virtual void BeginPlay() override;

public:

	AMachineGun();

	virtual void FireWeapon(bool bClientOnlyFire) override;
};
