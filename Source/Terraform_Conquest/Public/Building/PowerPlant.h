// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "Building/Building.h"
#include "PowerPlant.generated.h"

/**
 * 
 */
UCLASS()
class TERRAFORM_CONQUEST_API APowerPlant : public ABuilding
{
	GENERATED_BODY()

private:
	FTimerHandle PowerTickTimer;
	FTimerHandle UpgradeTimer;

protected:
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "PowerInfo")
	int32 PowerPerTick = 2;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "PowerInfo")
	float TimePerTick = 0.5f;

public:

	virtual void BeginPlay() override;

	void StarUpgrade();
	void StartPowerTick();
	UFUNCTION()
	void TickPower();

};
