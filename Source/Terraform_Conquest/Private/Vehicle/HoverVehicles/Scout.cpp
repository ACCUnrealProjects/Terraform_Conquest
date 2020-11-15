// Alex Chatt Terraform_Conquest 2020


#include "../../../Public/Vehicle/HoverVehicles/Scout.h"
#include "../../../Public/Components/Hover_Component.h"
#include "../Public/Components/Weapon_Controller_Component.h"

AScout::AScout()
{
	ForwardThrust = 175000.0f;

	WeaponController = CreateDefaultSubobject<UWeapon_Controller_Component>(TEXT("MyWeaponSystem"));
	WeaponController->bEditableWhenInherited = true;

	UHover_Component* AddedHoverComp = CreateDefaultSubobject<UHover_Component>(TEXT("SupportBooster1"));
	AddedHoverComp->bEditableWhenInherited = true;
	AddedHoverComp->SetupAttachment(MyMesh);
	AdditionalHoverComp.Add(AddedHoverComp);
}
