// Alex Chatt Terraform_Conquest 2020

#include "Vehicle/HoverVehicles/Scout.h"
#include "Components/Hover_Component.h"
#include "Components/Weapon_Controller_Component.h"

AScout::AScout()
{
	ForwardThrust = 1200.0f;
}

void AScout::BeginPlay()
{
	Super::BeginPlay();
	MainHoverComp->SetUp(50.0f, 4000.0f, 6.0f);
}