// Alex Chatt Terraform_Conquest 2020

#include "Projectile/MorterProjectile/Morter_Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

AMorter_Projectile::AMorter_Projectile()
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
	ProjectileMovement->InitialSpeed = MorterSpeed;
	ProjectileMovement->ProjectileGravityScale = 1.0f;
	ProjectileMovement->Bounciness = 0.0f;
	ProjectileMovement->Friction = 0.0f;
	ProjectileMovement->InterpLocationTime = 0.0f;

	TrailEffect = CreateDefaultSubobject<UParticleSystemComponent>(FName(TEXT("Trace Effect")));
	TrailEffect->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	TrailEffect->bAutoActivate = true;

	ImpactBlast = CreateDefaultSubobject<UParticleSystem>(FName(TEXT("Impact Blast")));

	ProjectileLifeTime = 300.0f;
}

// Called when the game starts or when spawned
void AMorter_Projectile::BeginPlay()
{
	AProjectile::BeginPlay();
	SphereCollider->OnComponentHit.AddDynamic(this, &AMorter_Projectile::OnHit);
}

void AMorter_Projectile::LaunchProjectile()
{
	ProjectileMovement->Activate();
	Super::LaunchProjectile();
}

void AMorter_Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor == GetOwner()) { return; }
	HitResponse(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);
}

void AMorter_Projectile::HitResponse(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor) { return; }

	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), DamageRadius, UDamageType::StaticClass(), TArray<AActor*>(), this, Cast<APawn>(GetOwner())->GetController(), true, ECC_Visibility);
	AProjectile::HitResponse(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);
}
