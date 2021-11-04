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

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "ProjectileType", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AProjectile> ProjectileBlueprint = nullptr;


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	class UParticleSystem* HitEffect = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	int32 DamagePerShot;

protected:

	virtual void BeginPlay() override;

	virtual void Fire() override;

public:

	APhasersWeapon();

	virtual void ChangeActiveState(const bool AmIActive) override;

	virtual void OnAttach(AActor* MyOwner, USceneComponent* OwnerMesh) override;
};
