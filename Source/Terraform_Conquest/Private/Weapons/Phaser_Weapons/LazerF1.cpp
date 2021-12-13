// Alex Chatt Terraform_Conquest 2020


#include "Weapons/Phaser_Weapons/LazerF1.h"

ALazerF1::ALazerF1()
{
	MaxAmmo = 10;
	CurrentTotalAmmo = MaxAmmo;
	AmmoRegenPercentage = 0.001f;
	WeaponName = "LazerF1";
	FireRate = 2.0f;
	Damage = 50.0f;
}