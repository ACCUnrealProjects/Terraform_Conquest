// Alex Chatt Terraform_Conquest 2020

#include "Projectile/Mines/Explode_Mine.h"
#include "Components/Health_Component.h"
#include "Kismet/GameplayStatics.h"

AExplode_Mine::AExplode_Mine()
{
	MyHealthComp->SetUp(20, 0);
	Damage = 100.0f;
	DamageRadius = TriggerRadius * 3.0f;
}

void AExplode_Mine::Trigger()
{
	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), DamageRadius, UDamageType::StaticClass(), TArray<AActor*>(), this, Cast<APawn>(GetOwner())->GetController(), false, ECC_Visibility);
	Super::Trigger();
}