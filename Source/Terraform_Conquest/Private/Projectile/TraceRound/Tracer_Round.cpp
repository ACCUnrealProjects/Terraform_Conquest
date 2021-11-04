// Alex Chatt Terraform_Conquest 2020

#include "Projectile/TraceRound/Tracer_Round.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

ATracer_Round::ATracer_Round()
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
	ProjectileMovement->InitialSpeed = TracerSpeed;
	ProjectileMovement->Bounciness = 0.0f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->Friction = 0.0f;
	ProjectileMovement->InterpLocationTime = 0.0f;

	TraceEffect = CreateDefaultSubobject<UParticleSystemComponent>(FName(TEXT("Trace Effect")));
	TraceEffect->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	TraceEffect->bAutoActivate = true;

	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void ATracer_Round::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMesh->OnComponentHit.AddDynamic(this, &ATracer_Round::OnHit);
}

void ATracer_Round::LaunchProjectile(AActor* Shooter)
{
	ProjectileMovement->Activate();
	Super::LaunchProjectile(Shooter);
}

void ATracer_Round::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	HitResponse(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);
}

void ATracer_Round::HitResponse(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ProjectileMesh->DestroyComponent();
	TraceEffect->Deactivate();

	Super::HitResponse(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);
}