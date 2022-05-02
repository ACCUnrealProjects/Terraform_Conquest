// Alex Chatt Terraform_Conquest 2020


#include "../../Public/Building/PowerPlant.h"

void APowerPlant::BeginPlay()
{
	StartPowerTick();
}

void APowerPlant::StarUpgrade()
{

}

void APowerPlant::StartPowerTick()
{
	GetWorld()->GetTimerManager().SetTimer(PowerTickTimer, this, &APowerPlant::TickPower, TimePerTick, true);
}

void APowerPlant::TickPower()
{
	//add power to team
}
