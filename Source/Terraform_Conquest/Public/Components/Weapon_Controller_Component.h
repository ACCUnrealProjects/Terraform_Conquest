// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponTypeEnum.h"
#include "Weapon_Controller_Component.generated.h"

class AWeapon;
class UWeaponPoint;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TERRAFORM_CONQUEST_API UWeapon_Controller_Component : public UActorComponent
{
	GENERATED_BODY()

private:	

	bool IsFiring = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	TArray<AWeapon*> AllGuns;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	AWeapon* ActiveWeapon = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	TArray<GunType> AllowedGunTypes;

	// Info for where to attach new guns to
	USceneComponent* MeshToAttachTo = nullptr;

	FActorSpawnParameters SpawnParams;

	void PlayerInputSetUp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	// Sets default values for this component's properties
	UWeapon_Controller_Component();

	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Weapon Setup
	void SwitchWeapon();
	void SwitchWeapon(GunType GunToLookFor);
	void AddWeapon(TSubclassOf<AWeapon> NewWeapon);
	void SetWeaponSlots(TArray<GunType> WeaponsICanHave);

	//Adding Ammo And Different Guns
	void AddAmmoForGuns(float AmmoPercent);
	bool CanIHaveGunType(GunType NewGunType);

	//Weapon Controls
	void FireCurrent();

	UFUNCTION(BlueprintCallable, Category = "WeaponInfo")
	AWeapon* GetCurrentGun() const;
	UFUNCTION(BlueprintCallable, Category = "WeaponInfo")
	FName GetWeaponWithIndexName(int32 index) const;

};
