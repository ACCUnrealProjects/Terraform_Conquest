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

	FString FireSocket1 = "RayFire1";
	FString FireSocket2 = "RayFire2";

	FTimerHandle AmmoRegenTimer;

	UFUNCTION()
	void AmmoRegen();

protected:

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "AmmoRegen")
	float AmmoRegenRate = 3.0f;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "AmmoRegen")
	int AmmoRegened = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	class UParticleSystem* HitEffect = nullptr;

	virtual void BeginPlay() override;

	virtual void Fire() override;

public:

	APhasersWeapon();

	virtual void ChangeActiveState(const bool AmIActive) override;

	virtual void OnAttach(AActor* MyOwner, USceneComponent* OwnerMesh) override;
};
