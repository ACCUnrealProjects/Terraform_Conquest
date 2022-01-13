// Alex Chatt Terraform_Conquest 2020

#include "Vehicle/HoverVehicles/Bombarder.h"
#include "Components/Hover_Component.h"
#include "Weapons/Machine_Guns/MachineGun.h"
#include "Components/Weapon_Controller_Component.h"
#include "WeaponTypeEnum.h"

ABombarder::ABombarder()
{
	ForwardThrust = 800.0f;
	VehicleName = "Bombarder";

	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/Meshes/Ships/craft_racer"));
	if (MeshObj.Succeeded())
	{
		MyMesh->SetStaticMesh(MeshObj.Object);
	}
	SetUpLights();

	VehicleWeaponControllerComp->AddSocketsForWeapons(GunType::MachineGun, TArray<FName>{"MachineGun_1", "MachineGun_2"});
	VehicleWeaponControllerComp->SetWeaponSlots(TArray<GunType>{GunType::MachineGun});
}

void ABombarder::BeginPlay()
{
	Super::BeginPlay();
}