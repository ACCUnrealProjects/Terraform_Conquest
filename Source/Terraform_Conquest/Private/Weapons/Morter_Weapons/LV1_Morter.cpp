// Alex Chatt Terraform_Conquest 2020


#include "Weapons/Morter_Weapons/LV1_Morter.h"

ALV1_Morter::ALV1_Morter()
{
	MaxAmmo = 20;
	CurrentTotalAmmo = MaxAmmo;
	AmmoRegenPercentage = 0.01f;
	WeaponName = "ALV1";
	FireRate = 1.5f;
}