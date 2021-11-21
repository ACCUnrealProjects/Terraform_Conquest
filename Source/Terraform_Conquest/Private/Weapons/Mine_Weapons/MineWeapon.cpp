// Alex Chatt Terraform_Conquest 2020

#include "Weapons/Mine_Weapons/MineWeapon.h"
#include "Projectile/Mines/Mine.h"

AMineWeapon::AMineWeapon()
{
	myWeaponType = GunType::Mine;
	AmmoRegened = 0;
}

void AMineWeapon::BeginPlay()
{
	Super::BeginPlay();
	Range = 150.0f;
}

void AMineWeapon::Fire()
{
	if (!ProjectileBlueprint) { return; }

	FVector DownVector = -GetActorUpVector();
	FVector DownPlacement = GetActorLocation() + (DownVector.GetSafeNormal() * Range);
	FHitResult DownCast;

	if (GetWorld()->LineTraceSingleByChannel(DownCast, GetActorLocation(), DownPlacement, ECollisionChannel::ECC_Camera, ShotParams))
	{
		GetWorld()->SpawnActor<AMine>(ProjectileBlueprint, DownCast.ImpactPoint, GetActorRotation(), ActorParams);
	}
	else
	{
		GetWorld()->SpawnActor<AMine>(ProjectileBlueprint, DownPlacement, GetActorRotation(), ActorParams);
	}

	AWeapon::Fire();

}


