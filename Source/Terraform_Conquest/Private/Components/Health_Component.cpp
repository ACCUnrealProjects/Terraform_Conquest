//Alex Chatt Terraform_Conquest 2020

#include "../../Public/Components/Health_Component.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UHealth_Component::UHealth_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealth_Component::BeginPlay()
{
	Super::BeginPlay();

	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		MyOwner->OnTakeAnyDamage.AddUniqueDynamic(this, &UHealth_Component::TakeDamage);
	}
}


// Called every frame
void UHealth_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealth_Component::SetMaxHealth(int32 StartHealth)
{
	MaxHealth = StartHealth;
	Health = StartHealth;
}

void UHealth_Component::IncreaseHealth(int32 HealthIncrease)
{
	Health = FMath::Min(Health + HealthIncrease, MaxHealth);
}

float UHealth_Component::GetHealthPercentage() const
{
	return (float)Health / (float)MaxHealth;
}

bool UHealth_Component::AmIAtMaxHealth() const
{
	return Health == MaxHealth;
}

bool UHealth_Component::AmIDead() const
{
	return Health <= 0;
}

void UHealth_Component::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	int32 intDamage = FPlatformMath::RoundToInt(Damage);
	intDamage = FMath::Clamp<int32>(intDamage, 0, Health);
	Health -= intDamage;

	if (Health <= 0)
	{
		IHaveDied.Broadcast();
	}
	else if (Damage > 0)
	{
		IHaveBeenHit.Broadcast();
	}
}

void UHealth_Component::KillMe()
{
	Health = 0;
	IHaveDied.Broadcast();
}