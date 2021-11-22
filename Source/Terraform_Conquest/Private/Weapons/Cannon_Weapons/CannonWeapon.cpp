// Alex Chatt Terraform_Conquest 2020

#include "Weapons/Cannon_Weapons/CannonWeapon.h"
#include "Projectile/CannonProjectile/Cannon_Projectile.h"
#include "Particles/ParticleSystemComponent.h"

ACannonWeapon::ACannonWeapon()
{
	myWeaponType = GunType::Cannon;

	FireEffect = CreateDefaultSubobject<UParticleSystemComponent>(FName("Cannon Fire Effect"));
	FireEffect->bAutoActivate = false;
	FireEffect->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	FireEffect->SetRelativeRotation(FRotator(0, -90.0f, 0));
}

void ACannonWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ACannonWeapon::Fire()
{
	//Fire Projectile
	if (!ProjectileBlueprint) { return; }

	//Fire Projectile
	ACannon_Projectile* CannonProjectile = GetWorld()->SpawnActor<ACannon_Projectile>(ProjectileBlueprint, GetActorLocation(), GetActorRotation(), ActorParams);
	CannonProjectile->LaunchProjectile();
	CurrentTotalAmmo--;

	AWeapon::Fire();
}

void ACannonWeapon::ChangeActiveState(const bool AmIActive)
{
	if (AmIActive)
	{
		GetWorld()->GetTimerManager().SetTimer(AmmoRegenTimer, this, &ACannonWeapon::AmmoRegen, AmmoRegened, true);
	}
	else if (!ExternalRegenOn)
	{
		GetWorld()->GetTimerManager().ClearTimer(AmmoRegenTimer);
	}
}
