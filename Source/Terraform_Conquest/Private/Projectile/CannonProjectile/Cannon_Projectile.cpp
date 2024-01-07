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
	ProjectileMesh->SetIsReplicated(true);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName(TEXT("Projectile Move Comp")));
	ProjectileMovement->bAutoActivate = true;
	ProjectileMovement->InitialSpeed = CannonSpeed;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->Bounciness = 0.0f;
	ProjectileMovement->Friction = 0.0f;
	ProjectileMovement->InterpLocationTime = 0.0f;

	TrailEffect = CreateDefaultSubobject<UParticleSystemComponent>(FName(TEXT("Trace Effect")));
	TrailEffect->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	TrailEffect->SetIsReplicated(true);
	TrailEffect->bAutoActivate = true;

	ProjectileLifeTime = 50.0f;
}

// Called when the game starts or when spawned
void ACannon_Projectile::BeginPlay()
{
	AProjectile::BeginPlay();
	if (HasAuthority())
	{
		SphereCollider->OnComponentHit.AddDynamic(this, &ACannon_Projectile::OnHit);
	}
}

void ACannon_Projectile::LaunchProjectile()
{
	ProjectileMovement->Activate();
}

void ACannon_Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor == GetOwner() || HitTarget) { return; }

	HitResponse(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);
}

void ACannon_Projectile::HitResponse(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::HitResponse(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);

	if (!OtherActor || !HasAuthority() || bClientOnlyProjectile) { return; }

	auto DamageDealer = (GetInstigator() && GetInstigator()->GetController()) ?
		GetInstigator()->GetController() : nullptr;

	UGameplayStatics::ApplyDamage(OtherActor, Damage, DamageDealer, this, UDamageType::StaticClass());

	SphereCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ProjectileMovement->StopMovementImmediately();
}
