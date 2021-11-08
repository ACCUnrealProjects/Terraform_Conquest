// Alex Chatt Terraform_Conquest 2020

#include "Weapons/Phaser_Weapons/PhasersWeapon.h"
#include "Projectile/Projectile.h"
#include "Particles/ParticleSystemComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

APhasersWeapon::APhasersWeapon()
{
	myWeaponType = GunType::Phasers;
}

void APhasersWeapon::BeginPlay()
{
	Super::BeginPlay();
	for (int32 i = 0; i < FireSockets.Num(); i++)
	{
		if (!MyOwnerMesh->DoesSocketExist(FName(FireSockets[i]))) { continue; }

		UParticleSystemComponent* PhasersEffect = CreateDefaultSubobject<UParticleSystemComponent>(FName(TEXT("Phasers Fire Effect" + FString::FromInt(i))));
		PhasersEffect->bAutoActivate = false;
		FVector SocketLocation = MyOwnerMesh->GetSocketLocation(FName(FireSockets[i]));

		FParticleSysParam Source;
		Source.Name = "Source";
		Source.ParamType = EParticleSysParamType::PSPT_Vector;
		Source.Vector = SocketLocation;
		PhasersEffect->InstanceParameters.Add(Source);

		FParticleSysParam Target;
		Target.Name = "Target";
		Target.ParamType = EParticleSysParamType::PSPT_Vector;
		Target.Vector = SocketLocation;
		PhasersEffect->InstanceParameters.Add(Target);

		PhasersEffect->SetBeamSourcePoint(0, SocketLocation, 0);
		PhasersEffect->SetBeamEndPoint(0, SocketLocation);

		FireEffect.Add(PhasersEffect);
	}
}

void APhasersWeapon::Fire()
{
	for (int i = 0; i < FireSockets.Num(); i++)
	{
		if (!MyOwnerMesh->DoesSocketExist(FName(FireSockets[i]))) { return; }

		//Raycast fire, also fire projectile flash or laser 
		FHitResult ShotHit;
		FVector RayStart = MyOwnerMesh->GetSocketLocation(FName(FireSockets[i]));
		FVector RayEnd = RayStart + (GetOwner()->GetActorForwardVector() * Range);

		if (GetWorld()->LineTraceSingleByChannel(ShotHit, RayStart, RayEnd, ECollisionChannel::ECC_Camera, ShotParams))
		{
			UGameplayStatics::ApplyDamage(ShotHit.GetActor(), DamagePerShot, Cast<APawn>(GetOwner())->GetController(), GetOwner(), UDamageType::StaticClass());
			DrawDebugLine(GetWorld(), RayStart, ShotHit.ImpactPoint, FColor(0, 255, 0), true, 0, 0, 10);
		}

		if (FireEffect.Num() < i && FireEffect[i] != nullptr)
		{
			FireEffect[i]->SetVectorParameter("Source", RayStart);
			FireEffect[i]->SetVectorParameter("Target", ShotHit.ImpactPoint);
			FireEffect[i]->SetBeamSourcePoint(0, RayStart, 0);
			FireEffect[i]->SetBeamEndPoint(0, ShotHit.ImpactPoint);
		}

		CurrentTotalAmmo--;
	}
	AWeapon::Fire();
}


void APhasersWeapon::ChangeActiveState(const bool AmIActive)
{
	if (AmIActive)
	{
		GetWorld()->GetTimerManager().SetTimer(AmmoRegenTimer, this, &APhasersWeapon::AmmoRegen, AmmoRegened, true);
	}
	else if(!ExternalRegenOn)
	{
		GetWorld()->GetTimerManager().ClearTimer(AmmoRegenTimer);
	}
}

void APhasersWeapon::OnAttach(AActor* MyOwner, USceneComponent* OwnerMesh)
{
	AWeapon::OnAttach(MyOwner, OwnerMesh);

	if (MyOwnerMesh)
	{
		for (int32 i = 0; i < FireEffect.Num(); i++)
		{
			if (FireSockets.Num() < i)
			{
				FireEffect[i]->AttachToComponent(MyOwnerMesh, FAttachmentTransformRules::KeepRelativeTransform, FName(FireSockets[i]));
			}	
		}
	}
}