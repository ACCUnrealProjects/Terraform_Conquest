// Alex Chatt Terraform_Conquest 2020

#include "../../Public/Weapons/MineWeapon.h"
#include "../../Public/Projectile/Mine.h"

AMineWeapon::AMineWeapon()
{
	myWeaponType = GunType::Mine;
}

void AMineWeapon::BeginPlay()
{
	Super::BeginPlay();
	Range = 150.0f;
	ShotParams.AddIgnoredActor(this);
}

void AMineWeapon::Fire()
{
	for (auto Socket : FireSockets)
	{
		if (!ensure(ProjectileBlueprint && MyOwnerMesh->DoesSocketExist(FName(Socket)))) { return; }

		FVector DownVector = -GetActorUpVector();
		FVector DownPlacement = MyOwnerMesh->GetSocketLocation(FName(Socket)) + (DownVector.GetSafeNormal() * Range);
		FHitResult DownCast;

		if (GetWorld()->LineTraceSingleByChannel(DownCast, GetActorLocation(), DownPlacement, ECollisionChannel::ECC_Camera, ShotParams))
		{
			AMine* Mine = GetWorld()->SpawnActor<AMine>(ProjectileBlueprint, DownCast.ImpactPoint, FRotator());
		}
		else
		{
			AMine* Mine = GetWorld()->SpawnActor<AMine>(ProjectileBlueprint, DownPlacement, FRotator());
		}

		AWeapon::Fire();
	}

}


