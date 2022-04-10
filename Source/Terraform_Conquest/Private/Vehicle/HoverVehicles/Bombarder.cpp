// Alex Chatt Terraform_Conquest 2020

#include "Vehicle/HoverVehicles/Bombarder.h"
#include "Components/Hover_Component.h"
#include "Components/Health_Component.h"
#include "Weapons/Machine_Guns/MachineGun.h"
#include "Weapons/Mine_Weapons/MineWeapon.h"
#include "Weapons/Morter_Weapons/MorterWeapon.h"
#include "Components/Weapon_Controller_Component.h"
#include "WeaponTypeEnum.h"

ABombarder::ABombarder()
{
	ForwardThrust = 1000.0f;
	VehicleName = "Bombarder";

	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/Meshes/Ships/craft_cargoA"));
	if (MeshObj.Succeeded())
	{
		MyMesh->SetStaticMesh(MeshObj.Object);
	}
	SetUpLights();

	VehicleWeaponControllerComp->AddSocketsForWeapons(GunType::MachineGun, TArray<FName>{"MachineGun_1", "MachineGun_2"});
	VehicleWeaponControllerComp->AddSocketsForWeapons(GunType::Mine, TArray<FName>{"MineSlot"});
	VehicleWeaponControllerComp->AddSocketsForWeapons(GunType::Morter, TArray<FName>{"MorterGun"});
	VehicleWeaponControllerComp->ServerSetWeaponSlots(TArray<GunType>{GunType::MachineGun, GunType::Morter, GunType::Mine});
}

void ABombarder::BeginPlay()
{
	Super::BeginPlay();
	//MainHoverComp->SetUp(50.0f, 5000.0f, 6.0f);
	MyHealth->SetUp(100.0f, 125.0f);
	VehicleWeaponControllerComp->AddWeapon(MachineGunBlueprint, GunType::MachineGun);
	VehicleWeaponControllerComp->AddWeapon(MorterGunBlueprint, GunType::Morter);
	VehicleWeaponControllerComp->AddWeapon(MineGunBlueprint, GunType::Mine);
	VehicleWeaponControllerComp->ServerChangeWeapon(GunType::MachineGun);

}