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
	for (const TPair <GunType, FWeaponContainer>& pair : AllGuns)
	{
		for (auto Gun : pair.Value.WeaponsList)
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
	if(WeaponSlotsMap.Contains(WeaponType))
	{
		WeaponSlotsMap[WeaponType].WeaponSlots = SlotNames;
		return;
	}

	FWeaponSlotList NewSlots;
	NewSlots.WeaponSlots = SlotNames;
	WeaponSlotsMap.Add(WeaponType, NewSlots);
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
			for (auto CurretGun : AllGuns[ActiveWeaponType].WeaponsList)
			{
				CurretGun->ChangeActiveState(false);
			}
			ActiveWeaponType = (GunType)SearchGunNum;
			for (auto CurretGun : AllGuns[ActiveWeaponType].WeaponsList)
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
		for (auto CurretGun : AllGuns[ActiveWeaponType].WeaponsList)
		{
			CurretGun->ChangeActiveState(false);
		}
	} 

	ActiveWeaponType = GunToLookFor;
	for (auto CurretGun : AllGuns[ActiveWeaponType].WeaponsList)
	{
		CurretGun->ChangeActiveState(true);
	}
}

void UWeapon_Controller_Component::AddWeapon(TSubclassOf<AWeapon> NewWeapon, GunType WeaponType)
{
	if (!NewWeapon || !CanIHaveGunType(WeaponType)) { return; }

	for (int32 i = 0; i < AllowedGunTypes.Num(); i++)
	{
		if (AllowedGunTypes[i] == WeaponType)
		{
			if (AllGuns.Contains(WeaponType))
			{
				for(int32 j = 0; j < AllGuns[WeaponType].WeaponsList.Num(); j++)
				{ 
					AllGuns[WeaponType].WeaponsList[j]->Destroy();
				}
				AllGuns[WeaponType].WeaponsList.Empty();
			}
			break;
		}
	}

	if (!AllGuns.Contains(WeaponType))
	{
		AllGuns.Add(WeaponType, FWeaponContainer());
	}

	for (auto WeaponSocket : WeaponSlotsMap[WeaponType].WeaponSlots)
	{
		AWeapon* NewGun = GetWorld()->SpawnActor<AWeapon>(NewWeapon, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(), SpawnParams);
		NewGun->AttachToActor(GetOwner(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), WeaponSocket);
		NewGun->ChangeActiveState(true);
		AllGuns[WeaponType].WeaponsList.Add(NewGun);
	}

	if (AllGuns.Contains(ActiveWeaponType))
	{
		for (auto CurretGun : AllGuns[ActiveWeaponType].WeaponsList)
		{
			CurretGun->ChangeActiveState(false);
		}
	}

	ActiveWeaponType = WeaponType;
}

void UWeapon_Controller_Component::FireCurrent()
{
	if (AllGuns.Contains(ActiveWeaponType))
	{
		for (auto Gun : AllGuns[ActiveWeaponType].WeaponsList)
		{
			Gun->AttemptToFire();
		}
	}
}

TArray<AWeapon*> UWeapon_Controller_Component::GetCurrentGuns() const
{
	if (ActiveWeaponType == GunType::None)
	{
		return TArray<AWeapon*>();
	}

	return AllGuns[ActiveWeaponType].WeaponsList;
}

FName UWeapon_Controller_Component::GetWeaponNameOfGunType(GunType GunType) const
{
	if (AllGuns.Contains(GunType) && AllGuns[GunType].WeaponsList.Num() > 0)
	{
		return AllGuns[GunType].WeaponsList[0]->GetWeaponName();
	}

	return FName(TEXT("N/A"));
}
