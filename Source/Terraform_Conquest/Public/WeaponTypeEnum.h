// Fill out your copyright notice in the Description page of Project Settings.

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
	Morter
};
