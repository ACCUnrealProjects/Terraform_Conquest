// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "TileIndex.generated.h"

USTRUCT(BlueprintType)
struct TERRAFORM_CONQUEST_API FTileIndex
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "XIndex")
	int32 XIndex = -1;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "YIndex")
	int32 YIndex = -1;
};
