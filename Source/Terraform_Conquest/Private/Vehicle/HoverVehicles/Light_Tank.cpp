// Alex Chatt Terraform_Conquest 2020

#include "Vehicle/HoverVehicles/Light_Tank.h"
#include "Components/Hover_Component.h"
#include "Components/Hover_Move_Component.h"
#include "Components/Health_Component.h"
#include "Weapons/Machine_Guns/MachineGun.h"
#include "Weapons/Cannon_Weapons/CannonWeapon.h"
#include "Weapons/Mine_Weapons/MineWeapon.h"
#include "Components/Weapon_Controller_Component.h"
#include "Utility/WeaponTypeEnum.h"

ALight_Tank::ALight_Tank()
{
	VehicleName = "Light Hover Tank";

	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/Meshes/Ships/craft_speederC"));
	if (MeshObj.Succeeded())
	{
		MyMesh->SetStaticMesh(MeshObj.Object);
	}
	SetUpLights();

	VehicleWeaponControllerComp->AddSocketsForWeapons(GunType::MachineGun, TArray<FName>{"MachineGun_1", "MachineGun_2"});
	VehicleWeaponControllerComp->AddSocketsForWeapons(GunType::MachineGun, TArray<FName>{"CannonGun_1"});
	VehicleWeaponControllerComp->AddSocketsForWeapons(GunType::MachineGun, TArray<FName>{"MineSlot"});
	VehicleWeaponControllerComp->ServerSetWeaponSlots(TArray<GunType>{GunType::MachineGun, GunType::Cannon, GunType::Mine});

	HoverMoveComp->SetTrusterSpeed(1000.0f);
}

void ALight_Tank::BeginPlay()
{
	Super::BeginPlay();
	HoverMoveComp->SetTrusterSpeed(1000.0f);
	MainHoverComp->SetUp(50.0f, 7000.0f, 6.0f);
	if (HasAuthority())
	{
		MyHealth->SetUp(100.0f, 125.0f);
		VehicleWeaponControllerComp->AddWeapon(MachineGunBlueprint, GunType::MachineGun);
		VehicleWeaponControllerComp->AddWeapon(CannonGunBlueprint, GunType::Cannon);
		VehicleWeaponControllerComp->AddWeapon(MineGunBlueprint, GunType::Mine);
		VehicleWeaponControllerComp->ServerChangeWeapon(GunType::MachineGun);
	}
}