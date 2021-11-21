// Alex Chatt Terraform_Conquest 2020

#include "Weapons/Machine_Guns/MachineGun.h"
#include "Projectile/TraceRound/Tracer_Round.h"
#include "Particles/ParticleSystemComponent.h"

AMachineGun::AMachineGun()
{
	myWeaponType = GunType::MachineGun;

	FireEffect = CreateDefaultSubobject<UParticleSystemComponent>(FName("Tracer Fire Effect"));
	FireEffect->bAutoActivate = false;
	FireEffect->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	FireEffect->SetRelativeRotation(FRotator(0, -90.0f, 0));
}

void AMachineGun::BeginPlay()
{
	Super::BeginPlay();
}

void AMachineGun::Fire()
{
	//Fire Projectile
	if (!ProjectileBlueprint) { return; }

	//Fire Projectile 
	ATracer_Round* TracerProjectile = GetWorld()->SpawnActor<ATracer_Round>(ProjectileBlueprint, GetActorLocation(), GetActorRotation(), ActorParams);
	TracerProjectile->LaunchProjectile(GetOwner());
	CurrentTotalAmmo--;

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
