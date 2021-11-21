// Alex Chatt Terraform_Conquest 2020

#include "Projectile/CannonProjectile/Cannon_Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ACannon_Projectile::ACannon_Projectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SphereCollider->SetVisibility(false);
	SphereCollider->SetNotifyRigidBodyCollision(true);
	SetRootComponent(SphereCollider);

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Collision Mesh")));
	ProjectileMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ProjectileMesh->SetRelativeLocation(FVector(0, 0, 0));
	ProjectileMesh->SetNotifyRigidBodyCollision(true);
	ProjectileMesh->SetVisibility(false);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName(TEXT("Projectile Move Comp")));
	ProjectileMovement->bAutoActivate = true;
	ProjectileMovement->InitialSpeed = CannonSpeed;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->Bounciness = 0.0f;
	ProjectileMovement->Friction = 0.0f;
	ProjectileMovement->InterpLocationTime = 0.0f;

	TrailEffect = CreateDefaultSubobject<UParticleSystemComponent>(FName(TEXT("Trace Effect")));
	TrailEffect->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	TrailEffect->bAutoActivate = true;

	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ProjectileLifeTime = 50.0f;
}

// Called when the game starts or when spawned
void ACannon_Projectile::BeginPlay()
{
	AProjectile::BeginPlay();
	ProjectileMesh->OnComponentHit.AddDynamic(this, &ACannon_Projectile::OnHit);
}

void ACannon_Projectile::LaunchProjectile(AActor* Shooter)
{
	ProjectileMovement->Activate();
	Super::LaunchProjectile(Shooter);
}

void ACannon_Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor == WhoShotMe) { return; }
	HitResponse(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);
}

void ACannon_Projectile::HitResponse(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AProjectile::HitResponse(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);
	UGameplayStatics::ApplyDamage(OtherActor, Damage, Cast<APawn>(WhoShotMe)->GetController(), WhoShotMe, UDamageType::StaticClass());
}
