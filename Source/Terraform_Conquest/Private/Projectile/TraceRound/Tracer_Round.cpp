// Alex Chatt Terraform_Conquest 2020

#include "Projectile/TraceRound/Tracer_Round.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

ATracer_Round::ATracer_Round()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Collision Mesh")));
	ProjectileMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ProjectileMesh->SetRelativeLocation(FVector(0, 0, 0));
	ProjectileMesh->SetNotifyRigidBodyCollision(true);
	ProjectileMesh->SetVisibility(false);
	SetRootComponent(ProjectileMesh);

	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void ATracer_Round::BeginPlay()
{
	ShotParams.AddIgnoredActor(GetOwner());
}

void ATracer_Round::Tick(float DeltaTime)
{
	FHitResult ShotHit;
	FVector RayStart = GetActorLocation();
	FVector RayEnd = RayStart + ((GetActorForwardVector() + FVector(0, 0, GetWorld()->GetGravityZ()))
		* TracerSpeed) * DeltaTime;

	if (GetWorld()->LineTraceSingleByChannel(ShotHit, RayStart, RayEnd, ECollisionChannel::ECC_Camera, ShotParams))
	{
		SetActorLocation(ShotHit.Location);
		HitResponse(ShotHit.Component.Get(), ShotHit.Actor.Get(), nullptr, ShotHit.ImpactNormal, ShotHit);
	}

	SetActorLocation(RayEnd);
}

void ATracer_Round::HitResponse(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ProjectileMesh->DestroyComponent();

	UGameplayStatics::ApplyDamage(OtherActor, Damage, Cast<APawn>(GetOwner())->GetController(), GetOwner(), UDamageType::StaticClass());

	Super::HitResponse(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);
}