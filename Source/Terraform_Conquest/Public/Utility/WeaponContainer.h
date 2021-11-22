// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "WeaponContainer.generated.h"

USTRUCT(BlueprintType)
struct TERRAFORM_CONQUEST_API FWeaponContainer
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponsList")
		TArray<class AWeapon*> WeaponsList;
};

USTRUCT(BlueprintType)
struct TERRAFORM_CONQUEST_API FWeaponSlotList
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponsSocketList")
		TArray<FName> WeaponSlots;
};
