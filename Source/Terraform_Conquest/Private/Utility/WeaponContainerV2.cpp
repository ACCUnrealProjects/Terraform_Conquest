// Alex Chatt Terraform_Conquest 2020

#include "Utility/WeaponContainerV2.h"
#include "Net/UnrealNetwork.h"
#include "Weapons/Weapon.h"

UWeaponContainerV2::UWeaponContainerV2() {  }

void UWeaponContainerV2::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UWeaponContainerV2, WeaponsType);
	DOREPLIFETIME(UWeaponContainerV2, WeaponsList);
	DOREPLIFETIME(UWeaponContainerV2, bReplicatedFlag);
}

void UWeaponContainerV2::ChangeActiveStateOfGuns(const bool bAmActive)
{
	for (auto Weapon : WeaponsList)
	{
		Weapon->ChangeActiveState(bAmActive);
	}
}
