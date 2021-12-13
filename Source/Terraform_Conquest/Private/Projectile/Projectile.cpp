// Alex Chatt Terraform_Conquest 2020

#include "../../Public/Projectile/Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	if (ProjectileLifeTime > 0.0f && GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(LifeTimer, this, &AProjectile::Death, ProjectileLifeTime, false);
	}
}

void AProjectile::HitResponse(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(ImpactBlast)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactBlast, Hit.Location + Hit.ImpactNormal, FRotator());
	}
	Death();
}

void AProjectile::Death()
{
	Destroy();
}

