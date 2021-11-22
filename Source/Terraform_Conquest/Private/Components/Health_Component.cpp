//Alex Chatt Terraform_Conquest 2020

#include "../../Public/Components/Health_Component.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UHealth_Component::UHealth_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UHealth_Component::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UHealth_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TimeSinceLastHit > 0.0f)
	{
		TimeSinceLastHit -= DeltaTime;
	}
	else if (TimeSinceLastHit <= 0.0f && Shield != MaxShield && !SheildRegenOn)
	{
		SheildRegenOn = true;
		GetWorld()->GetTimerManager().SetTimer(SheildRegenTickTimer, this, &UHealth_Component::SheildRegenTick, ShieldRegenRate, false);
	}
}

void UHealth_Component::SheildRegenTick()
{
	IncreaseShield(ShieldRegenPerTick);
	if (Shield < MaxShield)
	{
		GetWorld()->GetTimerManager().SetTimer(SheildRegenTickTimer, this, &UHealth_Component::SheildRegenTick, ShieldRegenRate, false);
	}
	else
	{
		SheildRegenOn = false;
	}
}


void UHealth_Component::SetUp(int32 StartHealth, int32 StartShield)
{
	MaxHealth = StartHealth;
	Health = StartHealth;

	MaxShield = StartShield;
	Shield = StartShield;
}

void UHealth_Component::IncreaseHealth(int32 HealthIncrease)
{
	Health = FMath::Min(Health + HealthIncrease, MaxHealth);
}

void UHealth_Component::IncreaseShield(int32 ShieldIncrease)
{
	Shield = FMath::Min(Shield + ShieldIncrease, MaxShield);
}

float UHealth_Component::GetHealthPercentage() const
{
	return (float)Health / (float)MaxHealth;
}

float UHealth_Component::GetShieldPercentage() const
{
	return (float)Shield / (float)MaxShield;
}

bool UHealth_Component::AmIAtMaxHealthAndShield() const
{
	return Health == MaxHealth && Shield == MaxShield;
}

bool UHealth_Component::AmIDead() const
{
	return Health <= 0;
}

float UHealth_Component::TakeDamage(float Damage)
{
	int32 intDamage = FPlatformMath::RoundToInt(Damage);
	intDamage = FMath::Clamp<int32>(intDamage, 0, Health);
	Health -= intDamage;

	if (Health <= 0)
	{
		IHaveDied.Broadcast();
	}

	//Sheild related changes
	TimeSinceLastHit = TimeBeforeShieldRegenBegins;
	GetWorld()->GetTimerManager().ClearTimer(SheildRegenTickTimer);
	SheildRegenOn = false;

	return intDamage;
}

void UHealth_Component::KillMe()
{
	Health = 0;
	IHaveDied.Broadcast();
}