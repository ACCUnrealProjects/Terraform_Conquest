// Alex Chatt Terraform_Conquest 2020

#include "Actor/Effects/Impact_Effect.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AImpact_Effect::AImpact_Effect()
{
	SetAutoDestroyWhenFinished(true);
}

// Called when the game starts or when spawned
void AImpact_Effect::BeginPlay()
{
	Super::BeginPlay();

	//UPhysicalMaterial* HitPhysMat = HitInfo.PhysMaterial.Get();

	if (ImpactBlast)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactBlast, GetActorLocation(), GetActorRotation());
	}

	if (DefaultSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DefaultSound, GetActorLocation());
	}

	if (DecalInfo.DecalMat)
	{
		FRotator DecalRotation = HitInfo.ImpactNormal.Rotation();

		UGameplayStatics::SpawnDecalAttached(DecalInfo.DecalMat, FVector(1.0f, DecalInfo.Size, DecalInfo.Size),
			HitInfo.Component.Get(), HitInfo.BoneName,
			HitInfo.ImpactPoint, DecalRotation, EAttachLocation::KeepWorldPosition,
			DecalInfo.LifeTime);
	}
	
}

