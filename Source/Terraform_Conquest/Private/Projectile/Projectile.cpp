// Alex Chatt Terraform_Conquest 2020

#include "Projectile/Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Actor/Effects/Impact_Effect.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	SetReplicateMovement(true);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	if (ProjectileLifeTime > 0.0f && HasAuthority())
	{
		GetWorld()->GetTimerManager().SetTimer(LifeTimer, this, &AProjectile::Death, ProjectileLifeTime, false);
	}
}

void AProjectile::HitResponse(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	bHaveHitSomething = true;
	SavedHit = Hit;

	if (HasAuthority())
	{
		Death();
	}
}

void AProjectile::Death()
{
	Destroy();
}

void AProjectile::Destroyed()
{
	// Only Spawn Effect/Sound if we have actually Hit something
	if (MyImpactEffect && bHaveHitSomething)
	{
		FTransform const SpawnTransform(SavedHit.ImpactNormal.Rotation(), SavedHit.Location);
		AImpact_Effect* EffectActor = GetWorld()->SpawnActorDeferred<AImpact_Effect>(MyImpactEffect, SpawnTransform);
		EffectActor->Set_HitResult(SavedHit);
	}
}


