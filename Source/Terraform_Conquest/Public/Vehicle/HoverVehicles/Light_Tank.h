// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "Vehicle/HoverVehicles/Hover_Vehicles.h"
#include "Light_Tank.generated.h"

/**
 * 
 */
UCLASS()
class TERRAFORM_CONQUEST_API ALight_Tank : public AHover_Vehicles
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "StartingWeapon", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class AMachineGun> MachineGunBlueprint = nullptr;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "StartingWeapon", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class ACannonWeapon> CannonGunBlueprint = nullptr;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "StartingWeapon", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class AMineWeapon> MineGunBlueprint = nullptr;

protected:

	virtual void BeginPlay() override;

public:

	ALight_Tank();
	
};
