// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "ProjectileHelp.generated.h"

USTRUCT()
struct FDecalInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Decal)
	UMaterial* DecalMat;

	UPROPERTY(EditDefaultsOnly, Category = Decal)
	float Size;

	UPROPERTY(EditDefaultsOnly, Category = Decal)
	float LifeTime;

	/** defaults */
	FDecalInfo()
	{
		DecalMat = nullptr;
		Size = 200.0f;
		LifeTime = 5.0f;
	}
};