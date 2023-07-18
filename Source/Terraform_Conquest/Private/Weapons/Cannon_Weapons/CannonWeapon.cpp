// Alex Chatt Terraform_Conquest 2020

#include "Weapons/Cannon_Weapons/CannonWeapon.h"
#include "Projectile/CannonProjectile/Cannon_Projectile.h"
#include "Particles/ParticleSystemComponent.h"

ACannonWeapon::ACannonWeapon()
{
	myWeaponType = GunType::Cannon;

	FireEffect = CreateDefaultSubobject<UParticleSystemComponent>(FName("Cannon Fire Effect"));
	FireEffect->bAutoActivate = false;
	FireEffect->SetIsReplicated(true);
	FireEffect->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	FireEffect->SetRelativeRotation(FRotator(0, -90.0f, 0));

	Range = 10000.0f;
}

void ACannonWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ACannonWeapon::FireWeapon()
{
	if (!ProjectileBlueprint) { return; }

	//Fire Projectile
	ACannon_Projectile* CannonProjectile = GetWorld()->SpawnActor<ACannon_Projectile>(ProjectileBlueprint, GetActorLocation(), GetActorRotation(), ActorParams);
	CannonProjectile->Tags.Add(FName(GetTeamName(TeamId)));
	CannonProjectile->LaunchProjectile();
	CurrentTotalAmmo--;
}
