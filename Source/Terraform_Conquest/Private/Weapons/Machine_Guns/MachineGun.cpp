// Alex Chatt Terraform_Conquest 2020

#include "Weapons/Machine_Guns/MachineGun.h"
#include "Projectile/TraceRound/Tracer_Round.h"
#include "Particles/ParticleSystemComponent.h"

AMachineGun::AMachineGun()
{
	myWeaponType = GunType::MachineGun;

	UParticleSystemComponent* MachineGunEffect = CreateDefaultSubobject<UParticleSystemComponent>(FName("Tracer Fire Effect"));
	MachineGunEffect->bAutoActivate = false;
	FireEffect.Add(MachineGunEffect);
}

void AMachineGun::BeginPlay()
{
	Super::BeginPlay();
}

void AMachineGun::Fire()
{
	//Fire Projectile
	for (auto Socket : FireSockets)
	{
		if (!ProjectileBlueprint || !MyOwnerMesh->DoesSocketExist(FName(Socket))) { return; }

		//Fire Projectile
		ATracer_Round* TracerProjectile = GetWorld()->SpawnActor<ATracer_Round>(ProjectileBlueprint, MyOwnerMesh->GetSocketLocation(FName(Socket)), MyOwnerMesh->GetSocketRotation(FName(Socket)));
		TracerProjectile->LaunchProjectile(GetOwner());
		CurrentTotalAmmo--;
	}

	AWeapon::Fire();
}

void AMachineGun::ChangeActiveState(const bool AmIActive)
{
	if (AmIActive)
	{
		GetWorld()->GetTimerManager().SetTimer(AmmoRegenTimer, this, &AMachineGun::AmmoRegen, AmmoRegened, true);
	}
	else if (!ExternalRegenOn)
	{
		GetWorld()->GetTimerManager().ClearTimer(AmmoRegenTimer);
	}
}

void AMachineGun::OnAttach(AActor* MyOwner, USceneComponent* OwnerMesh)
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