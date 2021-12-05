// Alex Chatt Terraform_Conquest 2020


#include "Weapons/Mine_Weapons/EM1_Deployer.h"

AEM1_Deployer::AEM1_Deployer()
{
	MaxAmmo = 10;
	CurrentTotalAmmo = MaxAmmo;
	AmmoRegenPercentage = 0.01f;
	WeaponName = "EM1";
	FireRate = 2.0f;
}