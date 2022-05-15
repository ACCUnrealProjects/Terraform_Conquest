// Alex Chatt Terraform_Conquest 2020

#include "Weapons/Mine_Weapons/MineWeapon.h"
#include "Projectile/Mines/Mine.h"

AMineWeapon::AMineWeapon()
{
	myWeaponType = GunType::Mine;
	AmmoRegened = 1;
	bCanIRegen = false;
	AmmoRegenRate = 5.0f;
}

void AMineWeapon::BeginPlay()
{
	Super::BeginPlay();
	Range = 150.0f;
}

void AMineWeapon::Fire_Implementation()
{
	AWeapon::Fire_Implementation();

	if (!ProjectileBlueprint) { return; }

	FVector DownVector = -GetActorUpVector();
	FVector DownPlacement = GetActorLocation() + (DownVector.GetSafeNormal() * Range);
	FHitResult DownCast;
	AMine* Mine = nullptr;

	if (GetWorld()->LineTraceSingleByChannel(DownCast, GetActorLocation(), DownPlacement, ECollisionChannel::ECC_Camera, ShotParams))
	{
		Mine = GetWorld()->SpawnActor<AMine>(ProjectileBlueprint, DownCast.ImpactPoint, GetActorRotation(), ActorParams);
	}
	else
	{
		Mine = GetWorld()->SpawnActor<AMine>(ProjectileBlueprint, DownPlacement, GetActorRotation(), ActorParams);
		Mine->SetTeamID(TeamId);
	}

	Mine->Tags.Add(FName(GetTeamName(TeamId)));
}


