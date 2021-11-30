// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Terraform_ConquestGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TERRAFORM_CONQUEST_API ATerraform_ConquestGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:

public:

private:

	ATerraform_ConquestGameModeBase();

public:

	virtual void StartPlay() override;
	
};
