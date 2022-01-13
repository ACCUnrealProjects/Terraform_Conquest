// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Utility/WeaponContainer.h"
#include "WeaponTypeEnum.h"
#include "Weapon_Controller_Component.generated.h"

class AWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TERRAFORM_CONQUEST_API UWeapon_Controller_Component : public UActorComponent
{
	GENERATED_BODY()

private:	

	bool IsFiring = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	TMap<GunType, FWeaponContainer> AllGuns;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	GunType ActiveWeaponType = GunType::None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	TArray<GunType> AllowedGunTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slots", meta = (AllowPrivateAccess = "true"))
	TMap<GunType, FWeaponSlotList> WeaponSlotsMap;

	// Info for where to attach new guns to
	USceneComponent* MeshToAttachTo = nullptr;

	FActorSpawnParameters SpawnParams;
	FCollisionQueryParams RayColParams;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	// Sets default values for this component's properties
	UWeapon_Controller_Component();

	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Weapon Setup
	void AddSocketsForWeapons(GunType WeaponType, TArray<FName> SlotNames);
	void AddWeapon(TSubclassOf<AWeapon> NewWeapon, GunType WeaponType);
	void SetWeaponSlots(TArray<GunType> WeaponsICanHave);

	//Switch Weapons 
	void SwitchWeapon();
	void SwitchWeapon(GunType GunToLookFor);

	//Rotate Weapon
	void RotateCurrentWeapons(FVector CamPos, FVector CamDirection);

	//Adding Ammo And Different Guns
	void StartRegenForGuns();
	void StopRegenForGuns();
	bool CanIHaveGunType(GunType NewGunType);

	//Weapon Controls
	void FireCurrent();

	UFUNCTION(BlueprintCallable, Category = "WeaponInfo")
	TArray<AWeapon*> GetCurrentGuns() const;
	UFUNCTION(BlueprintCallable, Category = "WeaponInfo")
	FName GetWeaponNameOfGunType(GunType GunType) const;

};
