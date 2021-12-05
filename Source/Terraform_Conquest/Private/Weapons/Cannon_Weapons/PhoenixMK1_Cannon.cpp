// Alex Chatt Terraform_Conquest 2020


#include "Weapons/Cannon_Weapons/PhoenixMK1_Cannon.h"

APhoenixMK1_Cannon::APhoenixMK1_Cannon()
{
	MaxAmmo = 100;
	CurrentTotalAmmo = MaxAmmo;
	AmmoRegenPercentage = 0.01f;
	WeaponName = "PhoenixMK1";
	FireRate = 0.75f;
}