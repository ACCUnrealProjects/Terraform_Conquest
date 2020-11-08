// Alex Chatt Terraform_Conquest 2020


#include "../../../Public/Vehicle/HoverVehicles/Scout.h"
#include "../Public/Components/Weapon_Controller_Component.h"

AScout::AScout()
{
	ForwardThrust = 250000.0f;

	WeaponController = CreateDefaultSubobject<UWeapon_Controller_Component>(TEXT("MyWeaponSystem"));
	WeaponController->bEditableWhenInherited = true;
}
