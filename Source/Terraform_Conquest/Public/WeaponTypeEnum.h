// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "UObject/Class.h"

UENUM(BlueprintType)
enum class GunType : uint8
{
	None,
	Cannon,
	Phasers,
	Mine,
	Morter,
	MachineGun,
};
