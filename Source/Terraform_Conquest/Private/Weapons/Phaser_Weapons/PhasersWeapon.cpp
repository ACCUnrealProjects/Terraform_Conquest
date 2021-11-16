// Alex Chatt Terraform_Conquest 2020

#include "Weapons/Phaser_Weapons/PhasersWeapon.h"
#include "Projectile/Projectile.h"
#include "Particles/ParticleSystemComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

APhasersWeapon::APhasersWeapon()
{
	myWeaponType = GunType::Phasers;

	UParticleSystemComponent* FireEffect = CreateDefaultSubobject<UParticleSystemComponent>(FName(TEXT("Phasers Fire Effect")));
	FireEffect->bAutoActivate = false;
	FireEffect->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	FParticleSysParam Source;
	Source.Name = "Source";
	Source.ParamType = EParticleSysParamType::PSPT_Vector;
	Source.Vector = GetActorLocation();
	FireEffect->InstanceParameters.Add(Source);

	FParticleSysParam Target;
	Target.Name = "Target";
	Target.ParamType = EParticleSysParamType::PSPT_Vector;
	Target.Vector = GetActorLocation();
	FireEffect->InstanceParameters.Add(Target);

	FireEffect->SetBeamSourcePoint(0, GetActorLocation(), 0);
	FireEffect->SetBeamEndPoint(0, GetActorLocation());
}

void APhasersWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void APhasersWeapon::Fire()
{
	//Raycast fire, also fire projectile flash or laser 
	FHitResult ShotHit;
	FVector RayStart = GetActorLocation();
	FVector RayEnd = RayStart + (GetActorForwardVector() * Range);

	if (GetWorld()->LineTraceSingleByChannel(ShotHit, RayStart, RayEnd, ECollisionChannel::ECC_Camera, ShotParams))
	{
		UGameplayStatics::ApplyDamage(ShotHit.GetActor(), Damage, Cast<APawn>(GetOwner())->GetController(), GetOwner(), UDamageType::StaticClass());
		DrawDebugLine(GetWorld(), RayStart, ShotHit.ImpactPoint, FColor(0, 255, 0), true, 0, 0, 10);
	}

	FireEffect->SetVectorParameter("Source", RayStart);
	FireEffect->SetVectorParameter("Target", ShotHit.ImpactPoint);
	FireEffect->SetBeamSourcePoint(0, RayStart, 0);
	FireEffect->SetBeamEndPoint(0, ShotHit.ImpactPoint);

	CurrentTotalAmmo--;

	AWeapon::Fire();
}


void APhasersWeapon::ChangeActiveState(const bool AmIActive)
{
	if (AmIActive)
	{
		GetWorld()->GetTimerManager().SetTimer(AmmoRegenTimer, this, &APhasersWeapon::AmmoRegen, AmmoRegened, true);
	}
	else if(!ExternalRegenOn)
	{
		GetWorld()->GetTimerManager().ClearTimer(AmmoRegenTimer);
	}
}