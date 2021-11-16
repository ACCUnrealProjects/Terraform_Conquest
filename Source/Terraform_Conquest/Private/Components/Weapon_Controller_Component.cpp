// Alex Chatt Terraform_Conquest 2020

#include "Components/Weapon_Controller_Component.h"
#include "Weapons/Weapon.h"
#include "Components/SceneComponent.h"

// Sets default values for this component's properties
UWeapon_Controller_Component::UWeapon_Controller_Component()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UWeapon_Controller_Component::BeginPlay()
{
	Super::BeginPlay();

	SpawnParams.Owner = GetOwner();
	SpawnParams.Instigator = Cast<APawn>(SpawnParams.Owner);

	MeshToAttachTo = GetOwner()->FindComponentByClass<USceneComponent>();
}

void UWeapon_Controller_Component::SetWeaponSlots(TArray<GunType> WeaponsICanHave)
{
	AllowedGunTypes = WeaponsICanHave;
}

void UWeapon_Controller_Component::AddAmmoForGuns(float AmmoPercent)
{
	for (const TPair <GunType, TArray<AWeapon*>>& pair : AllGuns)
	{
		for (auto Gun : pair.Value)
		{
			Gun->AddAmmo(AmmoPercent);
		}
	}
}

bool UWeapon_Controller_Component::CanIHaveGunType(GunType NewGunType)
{
	for (auto AllowedGunType : AllowedGunTypes)
	{
		if (AllowedGunType == NewGunType)
		{
			return true;
		}
	}
	return false;
}

void UWeapon_Controller_Component::AddSocketsForWeapons(GunType WeaponType, TArray<FName> SlotNames)
{
	WeaponSlotsMap[WeaponType] = SlotNames;
}

void UWeapon_Controller_Component::SwitchWeapon()
{
	if (AllGuns.Num() <= 0) { return; }

	bool FinishedLooking = false;
	int32 SearchGunNum = (uint8)ActiveWeaponType;
	int32 CurrentGunIndex = SearchGunNum;

	while (FinishedLooking == false)
	{
		SearchGunNum = FMath::Clamp(SearchGunNum, 1, 5);
		if (SearchGunNum == CurrentGunIndex)
		{
			FinishedLooking = true;
			break;
		}
		else if (AllGuns.Contains((GunType)SearchGunNum))
		{
			FinishedLooking = true;
			for (auto CurretGun : AllGuns[ActiveWeaponType])
			{
				CurretGun->ChangeActiveState(false);
			}
			ActiveWeaponType = (GunType)SearchGunNum;
			for (auto CurretGun : AllGuns[ActiveWeaponType])
			{
				CurretGun->ChangeActiveState(true);
			}
			break;
		}
		else
		{
			SearchGunNum++;
		}
	}
}

void UWeapon_Controller_Component::SwitchWeapon(GunType GunToLookFor)
{
	if (AllGuns.Num() <= 0 || !AllGuns.Contains(GunToLookFor)) { return; }

	if (AllGuns.Contains(ActiveWeaponType))
	{
		for (auto CurretGun : AllGuns[ActiveWeaponType])
		{
			CurretGun->ChangeActiveState(false);
		}
	} 

	ActiveWeaponType = GunToLookFor;
	for (auto CurretGun : AllGuns[ActiveWeaponType])
	{
		CurretGun->ChangeActiveState(true);
	}
}

void UWeapon_Controller_Component::AddWeapon(TSubclassOf<AWeapon> NewWeapon, GunType WeaponType)
{
	if (!NewWeapon) { return; }

	for (int32 i = 0; i < AllowedGunTypes.Num(); i++)
	{
		if (AllowedGunTypes[i] == WeaponType)
		{
			if (AllGuns.Contains(WeaponType))
			{
				for(int i = 0; i < AllGuns[WeaponType].Num(); i++)
				{ 
					AllGuns[WeaponType][i]->Destroy();
					i--;
				}
			}
			break;
		}
	}

	if (WeaponSlotsMap.Contains(WeaponType))
	{
		for (auto WeaponSocket : WeaponSlotsMap[WeaponType])
		{
			AWeapon* NewGun = GetWorld()->SpawnActor<AWeapon>(NewWeapon, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(), SpawnParams);
			NewGun->AttachToActor(GetOwner(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), WeaponSocket);
		}
	}

	if (AllGuns.Contains(ActiveWeaponType))
	{
		for (auto CurretGun : AllGuns[ActiveWeaponType])
		{
			CurretGun->ChangeActiveState(false);
		}
	}
	ActiveWeaponType = WeaponType;
	for (auto CurretGun : AllGuns[ActiveWeaponType])
	{
		CurretGun->ChangeActiveState(true);
	}
}

void UWeapon_Controller_Component::FireCurrent()
{
	if (AllGuns.Contains(ActiveWeaponType))
	{
		for (auto Gun : AllGuns[ActiveWeaponType])
		{
			Gun->AttemptToFire();
		}
	}
}

TArray<AWeapon*> UWeapon_Controller_Component::GetCurrentGun() const
{
	if (ActiveWeaponType == GunType::None)
	{
		return TArray<AWeapon*>();
	}

	return AllGuns[ActiveWeaponType];
}

FName UWeapon_Controller_Component::GetWeaponNameOfGunType(GunType GunType) const
{
	if (AllGuns.Contains(GunType) && AllGuns[GunType].Num() > 0)
	{
		return AllGuns[GunType][0]->GetWeaponName();
	}

	return FName(TEXT(""));
}
