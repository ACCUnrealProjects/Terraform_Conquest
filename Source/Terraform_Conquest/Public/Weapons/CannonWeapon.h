// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Weapon.h"
#include "CannonWeapon.generated.h"

/**
 * 
 */
UCLASS()
class TERRAFORM_CONQUEST_API ACannonWeapon : public AWeapon
{
	GENERATED_BODY()

private:

	FString FireSocket1 = "CannonFire";

	FTimerHandle AmmoRegenTimer;

	UFUNCTION()
	void AmmoRegen();
			
protected:

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "AmmoRegen")
	float AmmoRegenRate = 3.0f;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "AmmoRegen")
	int AmmoRegened = 1;

	virtual void BeginPlay() override;

	virtual void Fire() override;

public:

	ACannonWeapon();

	virtual void ChangeActiveState(const bool AmIActive) override;

	virtual void OnAttach(AActor* MyOwner, USceneComponent* OwnerMesh) override;
	
};
