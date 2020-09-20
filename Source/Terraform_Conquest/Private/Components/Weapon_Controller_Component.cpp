// Alex Chatt Terraform_Conquest 2020

#include "../../Public/Components/Weapon_Controller_Component.h"
#include "../../Public/Weapons/Weapon.h"
#include "Components/SceneComponent.h"

// Sets default values for this component's properties
UWeapon_Controller_Component::UWeapon_Controller_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UWeapon_Controller_Component::BeginPlay()
{
	Super::BeginPlay();

	SpawnParams.Owner = GetOwner();
	SpawnParams.Instigator = Cast<APawn>(GetOwner());
}

void UWeapon_Controller_Component::SetAttachSkel(USceneComponent* AttachWeaponTo)
{
	MeshToAttachTo = AttachWeaponTo;
}

void UWeapon_Controller_Component::SetWeaponSlots(TArray<GunType> WeaponsICanHave)
{
	AllowedGunTypes = WeaponsICanHave;
	AllGuns.Init(nullptr, AllowedGunTypes.Num());
}

void UWeapon_Controller_Component::AddAmmoForGuns(float AmmoPercent)
{
	for (int32 i = 0; i < AllGuns.Num(); i++)
	{
		if (AllGuns[i]) 
		{ 
			AllGuns[i]->AddAmmo(AmmoPercent);
		}
	}
}

bool UWeapon_Controller_Component::CanIHaveGunType(GunType NewGunType)
{
	for (int32 i = 0; i < AllowedGunTypes.Num(); i++)
	{
		if (AllowedGunTypes[i] == NewGunType)
		{
			return true;
		}
	}
	return false;
}


void UWeapon_Controller_Component::SwitchWeapon()
{
	bool FinishedLooking = false;
	int SearchGunNum = WeaponIndex + 1;

	while (FinishedLooking == false)
	{
		SearchGunNum = FMath::Clamp(SearchGunNum, 0, AllGuns.Num());
		if (SearchGunNum == WeaponIndex)
		{
			FinishedLooking = true;
			break;
		}
		else if (AllGuns[SearchGunNum])
		{
			FinishedLooking = true;
			break;
			AllGuns[WeaponIndex]->ChangeActiveState(false);
			WeaponIndex = SearchGunNum;
			AllGuns[WeaponIndex]->ChangeActiveState(true);

		}
		else
		{
			SearchGunNum++;
		}
	}

}

void UWeapon_Controller_Component::SwitchWeapon(GunType GunToLookFor)
{
	int32 GunSlot = 0;
	for (int32 i = 0; i < AllowedGunTypes.Num(); i++)
	{
		if (AllowedGunTypes[i] == GunToLookFor)
		{
			GunSlot = i;
			break;
		}
	}

	if (WeaponIndex == GunSlot || AllGuns[GunSlot] == nullptr) { return; }
	AllGuns[WeaponIndex]->ChangeActiveState(false);
	WeaponIndex = GunSlot;
	AllGuns[WeaponIndex]->ChangeActiveState(true);
}


void UWeapon_Controller_Component::AddWeapon(TSubclassOf<AWeapon> NewWeapon, FString PointToEquipTo, GunType myWeaponType)
{
	if (!NewWeapon) { return; }
	AWeapon* NewGun = GetWorld()->SpawnActor<AWeapon>(NewWeapon, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(), SpawnParams);
	if (WeaponIndex < 0) { WeaponIndex = 0; }
	NewGun->AttachToComponent(MeshToAttachTo, FAttachmentTransformRules::KeepRelativeTransform);
	NewGun->OnAttach(GetOwner(), MeshToAttachTo);
	int32 GunSlot = 0;
	for (int32 i = 0; i < AllowedGunTypes.Num(); i++)
	{
		if (AllowedGunTypes[i] == myWeaponType)
		{
			GunSlot = i;
			if (AllGuns[i] != nullptr)
			{
				AllGuns[i]->Destroy();
			}
			break;
		}
	}

	if (AllGuns[WeaponIndex])
	{
		AllGuns[WeaponIndex]->ChangeActiveState(false);
	}
	WeaponIndex = GunSlot;
	AllGuns[WeaponIndex] = NewGun;
	AllGuns[WeaponIndex]->ChangeActiveState(true);
}

void UWeapon_Controller_Component::FireCurrent()
{
	if (AllGuns[WeaponIndex])
	{
		AllGuns[WeaponIndex]->AttemptToFire();
	}
}

AWeapon* UWeapon_Controller_Component::GetCurrentGun()
{
	if (WeaponIndex < 0) { return nullptr; }
	return AllGuns[WeaponIndex];
}
