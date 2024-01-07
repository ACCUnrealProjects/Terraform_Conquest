// Alex Chatt Terraform_Conquest 2020

#include "Projectile/TraceRound/Tracer_Round.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ATracer_Round::ATracer_Round()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Collision Mesh")));
	ProjectileMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ProjectileMesh->SetRelativeLocation(FVector(0, 0, 0));
	ProjectileMesh->SetNotifyRigidBodyCollision(true);
	ProjectileMesh->SetVisibility(true);
	ProjectileMesh->SetCollisionProfileName("NoCollision");
	ProjectileMesh->SetIsReplicated(true);
	SetRootComponent(ProjectileMesh);

	ProjectileLifeTime = 15.0f;
}

void ATracer_Round::BeginPlay()
{
	Super::BeginPlay();
	HitTarget = false;
	if (HasAuthority() && GetOwner())
	{
		ShotParams.AddIgnoredActor(GetOwner());
		ShotParams.AddIgnoredActor(GetOwner()->GetOwner());
	}
}

void ATracer_Round::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (HitTarget) { return; }

	if (HasAuthority())
	{
	  FHitResult ShotHit;
	  FVector RayStart = GetActorLocation();
	  FVector Velocity = (GetActorForwardVector() * TracerSpeed) + (FVector(0, 0, GetWorld()->GetGravityZ()) * DeltaTime);
	  FVector RayEnd = RayStart + (Velocity * DeltaTime);
      SetActorLocation(RayEnd);

	  if (GetWorld()->LineTraceSingleByChannel(ShotHit, RayStart, RayEnd, ECollisionChannel::ECC_Camera, ShotParams))
	  {
		  HitTarget = true;
		  SetActorLocation(ShotHit.Location);
		  HitResponse(ShotHit.Component.Get(), ShotHit.Actor.Get(), nullptr, ShotHit.ImpactNormal, ShotHit);
	  }
	}
	
}

void ATracer_Round::LaunchProjectile()
{
	return;
}

void ATracer_Round::HitResponse(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::HitResponse(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);

	if (!OtherActor || !HasAuthority() || bClientOnlyProjectile) { return; }

	auto DamageDealer = (GetInstigator() && GetInstigator()->GetController()) ?
		GetInstigator()->GetController() : nullptr;

	UGameplayStatics::ApplyDamage(OtherActor, Damage, DamageDealer, this, UDamageType::StaticClass());
}