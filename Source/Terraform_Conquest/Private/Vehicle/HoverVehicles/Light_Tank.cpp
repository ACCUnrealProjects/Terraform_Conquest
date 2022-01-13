// Alex Chatt Terraform_Conquest 2020

#include "Vehicle/HoverVehicles/Light_Tank.h"
#include "Components/Hover_Component.h"
#include "Weapons/Machine_Guns/MachineGun.h"
#include "Components/Weapon_Controller_Component.h"
#include "WeaponTypeEnum.h"

ALight_Tank::ALight_Tank()
{
	ForwardThrust = 1000.0f;
	VehicleName = "Light Hover Tank";

	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/Meshes/Ships/craft_racer"));
	if (MeshObj.Succeeded())
	{
		MyMesh->SetStaticMesh(MeshObj.Object);
	}
	SetUpLights();

	VehicleWeaponControllerComp->AddSocketsForWeapons(GunType::MachineGun, TArray<FName>{"MachineGun_1", "MachineGun_2"});
	VehicleWeaponControllerComp->SetWeaponSlots(TArray<GunType>{GunType::MachineGun});
}

void ALight_Tank::BeginPlay()
{
	Super::BeginPlay();
}