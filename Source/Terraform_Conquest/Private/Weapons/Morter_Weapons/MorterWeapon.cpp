// Alex Chatt Terraform_Conquest 2020

#include "Weapons/Morter_Weapons/MorterWeapon.h"
#include "Projectile/MorterProjectile/Morter_Projectile.h"
#include "Particles/ParticleSystemComponent.h"

AMorterWeapon::AMorterWeapon()
{
	myWeaponType = GunType::Morter;

	UParticleSystemComponent* MorterEffect = CreateDefaultSubobject<UParticleSystemComponent>(FName("Morter Fire Effect"));
	MorterEffect->bAutoActivate = false;
	FireEffect.Add(MorterEffect);

	FireSockets.Add("MorterGun");
}

void AMorterWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AMorterWeapon::Fire()
{
	//Fire Projectile
	for (auto Socket : FireSockets)
	{
		if (!ProjectileBlueprint || !MyOwnerMesh->DoesSocketExist(FName(Socket))) { return; }

		//Fire Projectile
		AMorter_Projectile* MorterProjectile = GetWorld()->SpawnActor<AMorter_Projectile>(ProjectileBlueprint, MyOwnerMesh->GetSocketLocation(FName(Socket)), MyOwnerMesh->GetSocketRotation(FName(Socket)));
		MorterProjectile->LaunchProjectile(GetOwner());
		CurrentTotalAmmo--;
	}

	AWeapon::Fire();
}

void AMorterWeapon::ChangeActiveState(const bool AmIActive)
{
	if (AmIActive)
	{
		GetWorld()->GetTimerManager().SetTimer(AmmoRegenTimer, this, &AMorterWeapon::AmmoRegen, AmmoRegened, true);
	}
	else if (!ExternalRegenOn)
	{
		GetWorld()->GetTimerManager().ClearTimer(AmmoRegenTimer);
	}
}

void AMorterWeapon::OnAttach(AActor* MyOwner, USceneComponent* OwnerMesh)
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