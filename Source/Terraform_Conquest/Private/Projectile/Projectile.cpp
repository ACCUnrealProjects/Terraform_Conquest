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

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Collision Mesh")));
	SetRootComponent(ProjectileMesh);
	ProjectileMesh->SetNotifyRigidBodyCollision(true);
	ProjectileMesh->SetVisibility(false);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName(TEXT("Projectile Move Comp")));
	ProjectileMovement->bAutoActivate = false;

	TraceEffect = CreateDefaultSubobject<UParticleSystemComponent>(FName(TEXT("Trace Effect")));
	TraceEffect->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName(TEXT("Impact Blast")));
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
}

void AProjectile::LaunchProjectile(float Speed, AActor* Shooter)
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovement->Activate();

	WhoShotMe = Shooter;
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	HitResponse(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);
}

void AProjectile::HitResponse(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	TraceEffect->Deactivate();
	ImpactBlast->Activate();
	SetRootComponent(ImpactBlast);
	ProjectileMesh->DestroyComponent();

	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AProjectile::Death, DeathTime, false);
}


void AProjectile::Death()
{
	Destroy();
}

