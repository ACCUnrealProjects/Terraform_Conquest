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

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName(TEXT("Impact Blast")));
	ImpactBlast->bAutoActivate = false;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	if (ProjectileLifeTime > 0.0f && GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(LifeTimer, this, &AProjectile::Death, ProjectileLifeTime, false);
	}
}

void AProjectile::LaunchProjectile(AActor* Shooter)
{
	WhoShotMe = Shooter;
}

void AProjectile::HitResponse(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(ImpactBlast)
	{
		ImpactBlast->Activate();
		SetRootComponent(ImpactBlast);
	}

	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(DeathTimer, this, &AProjectile::Death, DeathTime, false);
	}
}

void AProjectile::Death()
{
	Destroy();
}

