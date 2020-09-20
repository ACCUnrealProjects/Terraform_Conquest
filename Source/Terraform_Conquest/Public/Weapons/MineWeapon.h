// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Weapon.h"
#include "MineWeapon.generated.h"

/**
 * 
 */
UCLASS()
class TERRAFORM_CONQUEST_API AMineWeapon : public AWeapon
{
	GENERATED_BODY()
	
private:

	FString FireSocket1 = "MinePlaceSocket";

protected:

	virtual void BeginPlay() override;

	virtual void Fire();

public:

	AMineWeapon();

	virtual void ChangeActiveState(const bool AmIActive) override;

	virtual void OnAttach(AActor* MyOwner, USceneComponent* OwnerMesh);

};
