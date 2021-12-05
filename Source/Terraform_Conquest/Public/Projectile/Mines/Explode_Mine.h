// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "Projectile/Mines/Mine.h"
#include "Explode_Mine.generated.h"

/**
 * 
 */
UCLASS()
class TERRAFORM_CONQUEST_API AExplode_Mine : public AMine
{
	GENERATED_BODY()

private:
	float DamageRadius = 1.0f;

public:

private:

protected:
	virtual void Trigger() override;

public:
	AExplode_Mine();
};
