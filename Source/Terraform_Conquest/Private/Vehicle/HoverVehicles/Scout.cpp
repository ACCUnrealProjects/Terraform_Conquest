// Alex Chatt Terraform_Conquest 2020


#include "../../../Public/Vehicle/HoverVehicles/Scout.h"
#include "../../../Public/Components/Hover_Component.h"
#include "../Public/Components/Weapon_Controller_Component.h"

AScout::AScout()
{
	ForwardThrust = 1200.0f;

	WeaponController = CreateDefaultSubobject<UWeapon_Controller_Component>(TEXT("MyWeaponSystem"));
	WeaponController->bEditableWhenInherited = true;
}

void AScout::BeginPlay()
{
	MainHoverComp->SetUp(50.0f, 4000.0f, 6.0f);
}