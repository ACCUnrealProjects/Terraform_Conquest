// Alex Chatt Terraform_Conquest 2020

#include "Projectile/Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Actor/Effects/Impact_Effect.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

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
	if (ProjectileLifeTime > 0.0f && (HasAuthority() || bClientOnlyProjectile))
	{
		SetLifeSpan(ProjectileLifeTime);
	}

	if (GetInstigator() && RootComponent 
		&& GetInstigator()->IsLocallyControlled() && !HasAuthority())
	{
		RootComponent->SetHiddenInGame(true);
	}
}

void AProjectile::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Replicate everywhere
	DOREPLIFETIME(AProjectile, SavedHit);
}

void AProjectile::SetClientOnlyProjectile()
{
	bClientOnlyProjectile = true;
}

void AProjectile::OnRep_SaveHit()
{
	if (!HasAuthority())
	{
		SpawnEffect();
		Destroy();
	}
}

void AProjectile::HitResponse(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	HitTarget = true;
	SavedHit = Hit;

	if (HasAuthority())
	{
		if (!bClientOnlyProjectile)
		{
			Death();
		}
		else
		{
			// Just destroy us for clients
			Destroy();
		}
	}
}

void AProjectile::SpawnEffect()
{	
	// Only Spawn Effect/Sound if we have actually Hit something
	if (MyImpactEffect && SavedHit.Actor.IsValid())
	{
		FTransform const SpawnTransform(SavedHit.ImpactNormal.Rotation(), SavedHit.Location);
		AImpact_Effect* EffectActor = GetWorld()->SpawnActorDeferred<AImpact_Effect>(MyImpactEffect, SpawnTransform);
		EffectActor->Set_HitResult(SavedHit);
		UGameplayStatics::FinishSpawningActor(EffectActor, SpawnTransform);
	}

}

void AProjectile::Death()
{
	// Give time to replicate to clients 
	SetLifeSpan(DestroyTime);
	if (ProjectileMesh) 
	{ 
		ProjectileMesh->SetVisibility(false);
	}
	SpawnEffect();
}



