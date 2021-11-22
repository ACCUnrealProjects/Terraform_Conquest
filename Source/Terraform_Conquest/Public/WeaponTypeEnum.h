// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "UObject/Class.h"

UENUM(BlueprintType)
enum class GunType : uint8
{
	None = 0,
	MachineGun = 1,
	Cannon = 2,
	Phasers = 3,
	Morter = 4,
	Mine = 5,
};
