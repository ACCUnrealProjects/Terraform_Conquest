// Alex Chatt Terraform_Conquest 2020

#include "Vehicle/HoverVehicles/Scout.h"
#include "Components/Hover_Component.h"
#include "Weapons/Machine_Guns/MachineGun.h"
#include "Components/Weapon_Controller_Component.h"
#include "WeaponTypeEnum.h"

AScout::AScout()
{
	ForwardThrust = 1200.0f;
	VehicleName = "Scout";

	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/Meshes/Ships/craft_racer"));
	if (MeshObj.Succeeded())
	{
		MyMesh->SetStaticMesh(MeshObj.Object);
	}
	SetUpLights();

	VehicleWeaponControllerComp->AddSocketsForWeapons(GunType::MachineGun, TArray<FName>{"MachineGun_1", "MachineGun_2"});
	VehicleWeaponControllerComp->ServerSetWeaponSlots(TArray<GunType>{GunType::MachineGun});
}

void AScout::BeginPlay()
{
	Super::BeginPlay();
	MainHoverComp->SetUp(50.0f, 5000.0f, 6.0f);
	VehicleWeaponControllerComp->AddWeapon(MachineGunBlueprint, GunType::MachineGun);
}