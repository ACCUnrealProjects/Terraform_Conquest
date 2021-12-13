// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Weapon.h"
#include "PhasersWeapon.generated.h"

/**
 * 
 */
UCLASS()
class TERRAFORM_CONQUEST_API APhasersWeapon : public AWeapon
{
	GENERATED_BODY()

private:


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
		class UParticleSystem* HitEffect = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
		int32 Damage = 1;

	UPROPERTY(BlueprintReadOnly, Category = "Range")
		float Range = 10000.0f;

protected:

	virtual void BeginPlay() override;

	virtual void Fire() override;

public:

	APhasersWeapon();
};
