// Alex Chatt Terraform_Conquest 2020

#include "Vehicle/HoverVehicles/Marauder.h"
#include "Components/Hover_Component.h"
#include "Components/Health_Component.h"
#include "Weapons/Machine_Guns/MachineGun.h"
#include "Weapons/Cannon_Weapons/CannonWeapon.h"
#include "Weapons/Mine_Weapons/MineWeapon.h"
#include "Components/Weapon_Controller_Component.h"
#include "Utility/WeaponTypeEnum.h"

AMarauder::AMarauder()
{
	ForwardThrust = 600.0f;
	VehicleName = "Marauder";

	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/Meshes/Ships/craft_cargoB"));
	if (MeshObj.Succeeded())
	{
		MyMesh->SetStaticMesh(MeshObj.Object);
	}
	SetUpLights();

	VehicleWeaponControllerComp->AddSocketsForWeapons(GunType::MachineGun, TArray<FName>{"MachineGun_1", "MachineGun_2"});
	VehicleWeaponControllerComp->ServerSetWeaponSlots(TArray<GunType>{GunType::MachineGun});
}

void AMarauder::BeginPlay()
{
	Super::BeginPlay();
	//MainHoverComp->SetUp(50.0f, 5000.0f, 6.0f);
	MyHealth->SetUp(150.0f, 150.0f);
	VehicleWeaponControllerComp->AddWeapon(MachineGunBlueprint, GunType::MachineGun);
	VehicleWeaponControllerComp->AddWeapon(CannonGunBlueprint, GunType::Cannon);
	VehicleWeaponControllerComp->AddWeapon(MineGunBlueprint, GunType::Mine);
	VehicleWeaponControllerComp->ServerChangeWeapon(GunType::MachineGun);
}
