// Alex Chatt Terraform_Conquest 2020

#include "Weapons/Morter_Weapons/MorterWeapon.h"
#include "Projectile/MorterProjectile/Morter_Projectile.h"
#include "Particles/ParticleSystemComponent.h"

AMorterWeapon::AMorterWeapon()
{
	myWeaponType = GunType::Morter;

	FireEffect = CreateDefaultSubobject<UParticleSystemComponent>(FName("Morter Fire Effect"));
	FireEffect->bAutoActivate = false;
	FireEffect->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	FireEffect->SetRelativeRotation(FRotator(0,-90.0f,0));
}

void AMorterWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AMorterWeapon::Fire()
{
	//Fire Projectile
	if (!ProjectileBlueprint) { return; }

	//Fire Projectile
	AMorter_Projectile* MorterProjectile = GetWorld()->SpawnActor<AMorter_Projectile>(ProjectileBlueprint, GetActorLocation(), GetActorRotation(), ActorParams);
	MorterProjectile->LaunchProjectile();
	CurrentTotalAmmo--;

	AWeapon::Fire();
}
