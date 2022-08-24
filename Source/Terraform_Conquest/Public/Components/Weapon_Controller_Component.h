// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Utility/WeaponTypeEnum.h"
#include "Weapon_Controller_Component.generated.h"

class AWeapon;
class UWeaponContainerV2;

USTRUCT(BlueprintType)
struct TERRAFORM_CONQUEST_API FWeaponSlotList
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WeaponsType")
		GunType WeaponsType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponsSocketList")
		TArray<FName> WeaponSlots;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TERRAFORM_CONQUEST_API UWeapon_Controller_Component : public UActorComponent
{
	GENERATED_BODY()

private:	

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	TArray<UWeaponContainerV2*> AllGuns;
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	UWeaponContainerV2* ActiveWeapon = nullptr;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	TArray<GunType> AllowedGunTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slots", meta = (AllowPrivateAccess = "true"))
	TArray<FWeaponSlotList> WeaponSlotsList;

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

	// Property replication 
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Needed to replicate UObject UWeaponContainerV2 
	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	//Weapon Setup
	void AddSocketsForWeapons(GunType WeaponType, TArray<FName> SlotNames);

	// Guns im allowed
	UFUNCTION(reliable, server, WithValidation)
		void ServerSetWeaponSlots(const TArray<GunType> &WeaponsICanHave);

	//Adding Weapon
	void AddWeapon(TSubclassOf<AWeapon> NewWeapon, GunType WeaponType);
	UFUNCTION(reliable, server, WithValidation)
		void ServerAddWeapon(TSubclassOf<AWeapon> NewWeapon, GunType WeaponType);

	//Switch Weapons 
	void SwitchWeapon();
	void SwitchWeapon(GunType GunToLookFor);
	
	//Change active weapon on server
	UFUNCTION(reliable, server, WithValidation)
		void ServerChangeWeapon(GunType NewWeapon);

	UFUNCTION(unreliable, server, WithValidation)
		void ServerRotateCurrentWeapons(FVector CamPos, FVector CamDirection);

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
