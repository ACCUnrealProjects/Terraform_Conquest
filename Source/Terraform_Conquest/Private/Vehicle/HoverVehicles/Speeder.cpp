// Alex Chatt Terraform_Conquest 2020

#include "Vehicle/HoverVehicles/Speeder.h"
#include "Components/Health_Component.h"
#include "Components/Hover_Move_Component.h"
#include "Components/Hover_Component.h"
#include "Weapons/Machine_Guns/MachineGun.h"
#include "Weapons/Mine_Weapons/MineWeapon.h"
#include "Components/Weapon_Controller_Component.h"
#include "Utility/WeaponTypeEnum.h"

ASpeeder::ASpeeder()
{
	VehicleName = "Speeder";

	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/Meshes/Ships/craft_speederA"));
	if (MeshObj.Succeeded())
	{
		MyMesh->SetStaticMesh(MeshObj.Object);
	}
	SetUpLights();

	VehicleWeaponControllerComp->AddSocketsForWeapons(GunType::MachineGun, TArray<FName>{"MachineGun_1", "MachineGun_2"});
	VehicleWeaponControllerComp->AddSocketsForWeapons(GunType::Mine, TArray<FName>{"MineSlot"});
	VehicleWeaponControllerComp->ServerSetWeaponSlots(TArray<GunType>{GunType::MachineGun, GunType::Mine});

	HoverMoveComp->SetTrusterSpeed(1500.0f);
}

void ASpeeder::BeginPlay()
{
	Super::BeginPlay();
	HoverMoveComp->SetTrusterSpeed(1500.0f);
	MainHoverComp->SetUp(50.0f, 7000.0f, 6.0f);
	if (HasAuthority())
	{
		MyHealth->SetUp(75.0f, 50.0f);
		VehicleWeaponControllerComp->AddWeapon(MachineGunBlueprint, GunType::MachineGun);
		VehicleWeaponControllerComp->AddWeapon(MineGunBlueprint, GunType::Mine);
		VehicleWeaponControllerComp->ServerChangeWeapon(GunType::MachineGun);
	}
}
