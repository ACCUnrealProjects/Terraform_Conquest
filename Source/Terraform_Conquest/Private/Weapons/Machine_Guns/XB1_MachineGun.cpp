// Alex Chatt Terraform_Conquest 2020


#include "Weapons/Machine_Guns/XB1_MachineGun.h"

AXB1_MachineGun::AXB1_MachineGun()
{
	MaxAmmo = 1000;
	CurrentTotalAmmo = MaxAmmo;
	AmmoRegened = MaxAmmo * 0.05;
	WeaponName = "XB1";
	FireRate = 0.25f;
}