// Alex Chatt Terraform_Conquest 2020

#include "Vehicle/HoverVehicles/Tank.h"
#include "Components/Hover_Component.h"
#include "Components/Health_Component.h"
#include "Components/Weapon_Controller_Component.h"
#include "Weapons/Machine_Guns/MachineGun.h"
#include "Weapons/Cannon_Weapons/CannonWeapon.h"
#include "Weapons/Mine_Weapons/MineWeapon.h"
#include "Utility/WeaponTypeEnum.h"

ATank::ATank()
{
	ForwardThrust = 900.0f;
	VehicleName = "Hover_Tank";

	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/Meshes/Ships/craft_miner"));
	if (MeshObj.Succeeded())
	{
		MyMesh->SetStaticMesh(MeshObj.Object);
	}
	SetUpLights();

	VehicleWeaponControllerComp->AddSocketsForWeapons(GunType::MachineGun, TArray<FName>{"MachineGun_1", "MachineGun_2"});
	VehicleWeaponControllerComp->AddSocketsForWeapons(GunType::Cannon, TArray<FName>{"CannonGun_1", "CannonGun_2"});
	VehicleWeaponControllerComp->AddSocketsForWeapons(GunType::Mine, TArray<FName>{"MineSlot"});
	VehicleWeaponControllerComp->ServerSetWeaponSlots(TArray<GunType>{GunType::MachineGun, GunType::Cannon, GunType::Mine});
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	MainHoverComp->SetUp(50.0f, 5000.0f, 6.0f);
	MyHealth->SetUp(125.0f, 125.0f);
	VehicleWeaponControllerComp->AddWeapon(MachineGunBlueprint, GunType::MachineGun);
	VehicleWeaponControllerComp->AddWeapon(CannonGunBlueprint, GunType::Cannon);
	VehicleWeaponControllerComp->AddWeapon(MineGunBlueprint, GunType::Mine);
	VehicleWeaponControllerComp->ServerChangeWeapon(GunType::MachineGun);
}