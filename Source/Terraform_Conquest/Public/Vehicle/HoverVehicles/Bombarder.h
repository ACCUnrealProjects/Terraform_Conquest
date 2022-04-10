// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "Vehicle/HoverVehicles/Hover_Vehicles.h"
#include "Bombarder.generated.h"

/**
 * 
 */
UCLASS()
class TERRAFORM_CONQUEST_API ABombarder : public AHover_Vehicles
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "StartingWeapon", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class AMachineGun> MachineGunBlueprint = nullptr;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "StartingWeapon", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class AMorterWeapon> MorterGunBlueprint = nullptr;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "StartingWeapon", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class AMineWeapon> MineGunBlueprint = nullptr;

protected:

	virtual void BeginPlay() override;

public:

	ABombarder();
	
};
