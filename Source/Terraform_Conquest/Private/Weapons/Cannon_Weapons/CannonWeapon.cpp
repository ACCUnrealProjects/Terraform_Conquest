// Alex Chatt Terraform_Conquest 2020

#include "Weapons/Cannon_Weapons/CannonWeapon.h"
#include "Projectile/CannonProjectile/Cannon_Projectile.h"
#include "Particles/ParticleSystemComponent.h"

ACannonWeapon::ACannonWeapon()
{
	myWeaponType = GunType::Cannon;

	UParticleSystemComponent *CannonEffect = CreateDefaultSubobject<UParticleSystemComponent>(FName("Cannon Fire Effect"));
	CannonEffect->bAutoActivate = false;
	FireEffect.Add(CannonEffect);
}

void ACannonWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ACannonWeapon::Fire()
{
	//Fire Projectile
	for (auto Socket : FireSockets)
	{
		if (!ProjectileBlueprint || !MyOwnerMesh->DoesSocketExist(FName(Socket))) { return; }

		//Fire Projectile
		ACannon_Projectile* CannonProjectile = GetWorld()->SpawnActor<ACannon_Projectile>(ProjectileBlueprint, MyOwnerMesh->GetSocketLocation(FName(Socket)), MyOwnerMesh->GetSocketRotation(FName(Socket)));
		CannonProjectile->LaunchProjectile(GetOwner());
		CurrentTotalAmmo--;
	}

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

void ACannonWeapon::OnAttach(AActor* MyOwner, USceneComponent* OwnerMesh)
{
	AWeapon::OnAttach(MyOwner, OwnerMesh);

	if (MyOwnerMesh)
	{
		for (int32 i = 0; i < FireEffect.Num(); i++)
		{
			if (FireSockets.Num() < i)
			{
				FireEffect[i]->AttachToComponent(MyOwnerMesh, FAttachmentTransformRules::KeepRelativeTransform, FName(FireSockets[i]));
			}
		}
	}
}