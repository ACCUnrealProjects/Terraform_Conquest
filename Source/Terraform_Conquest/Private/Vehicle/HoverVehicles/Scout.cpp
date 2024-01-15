// Alex Chatt Terraform_Conquest 2020

#include "Vehicle/HoverVehicles/Scout.h"
#include "Components/Hover_Component.h"
#include "Components/Hover_Move_Component.h"
#include "Components/Health_Component.h"
#include "Weapons/Machine_Guns/MachineGun.h"
#include "Weapons/Cannon_Weapons/CannonWeapon.h"
#include "Weapons/Mine_Weapons/MineWeapon.h"
#include "Components/Weapon_Controller_Component.h"
#include "Utility/WeaponTypeEnum.h"

AScout::AScout()
{
	VehicleName = "Scout";

	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/Meshes/Ships/craft_speederC"));
	if (MeshObj.Succeeded())
	{
		MyMesh->SetStaticMesh(MeshObj.Object);
	}
	SetUpLights();

	VehicleWeaponControllerComp->AddSocketsForWeapons(GunType::MachineGun, TArray<FName>{"MachineGun_1", "MachineGun_2"});
	VehicleWeaponControllerComp->AddSocketsForWeapons(GunType::Mine, TArray<FName>{"MineSlot"});
	VehicleWeaponControllerComp->ServerSetWeaponSlots(TArray<GunType>{GunType::MachineGun, GunType::Cannon, GunType::Mine});

	HoverMoveComp->SetTrusterSpeed(800.0f);
}

void AScout::BeginPlay()
{
	Super::BeginPlay();
	MainHoverComp->SetUp(50.0f, 6000.0f, 5.0f);
	HoverMoveComp->SetTrusterSpeed(800.0f);
	if (HasAuthority())
	{
		MyHealth->SetUp(100.0f, 100.0f);
		VehicleWeaponControllerComp->AddWeapon(MachineGunBlueprint, GunType::MachineGun);
		VehicleWeaponControllerComp->AddWeapon(MineGunBlueprint, GunType::Mine);
		VehicleWeaponControllerComp->ServerChangeWeapon(GunType::MachineGun);
	}
}