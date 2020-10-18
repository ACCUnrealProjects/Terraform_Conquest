// Alex Chatt Terraform_Conquest 2020

#include "../../Public/Weapons/PhasersWeapon.h"
#include "../../Public/Projectile/Projectile.h"
#include "Particles/ParticleSystemComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

APhasersWeapon::APhasersWeapon()
{
	myWeaponType = GunType::Phasers;

	UParticleSystemComponent* PhasersEffect1 = CreateDefaultSubobject<UParticleSystemComponent>(FName(TEXT("Phasers Fire Effect 1")));
	PhasersEffect1->bAutoActivate = false;
	FireEffect.Add(PhasersEffect1);

	UParticleSystemComponent* PhasersEffect2 = CreateDefaultSubobject<UParticleSystemComponent>(FName(TEXT("Phasers Fire Effect 2")));
	PhasersEffect2->bAutoActivate = false;
	FireEffect.Add(PhasersEffect2);

	FireSockets.Add(TEXT("RayFire1"));
	FireSockets.Add(TEXT("RayFire2"));
}

void APhasersWeapon::BeginPlay()
{
	for (int32 i = 0; i < FireSockets.Num(); i++)
	{
		UParticleSystemComponent* PhasersEffect = CreateDefaultSubobject<UParticleSystemComponent>(FName(TEXT("Phasers Fire Effect" + FString::FromInt(i))));
		PhasersEffect->bAutoActivate = false;
		FireEffect.Add(PhasersEffect);
	}
}

void APhasersWeapon::Fire()
{
	for (auto Socket : FireSockets)
	{
		if (!ensure(MyOwnerMesh->DoesSocketExist(FName(Socket)))) { return; }

		//Raycast fire, also fire projectile flash or laser 
		FHitResult ShotHit;
		FVector RayStart = MyOwnerMesh->GetSocketLocation(FName(Socket));
		FVector RayEnd = RayStart + (GetOwner()->GetActorForwardVector() * Range);

		if (GetWorld()->LineTraceSingleByChannel(ShotHit, RayStart, RayEnd, ECollisionChannel::ECC_Camera, ShotParams))
		{
			UGameplayStatics::ApplyDamage(ShotHit.GetActor(), DamagePerShot, Cast<APawn>(GetOwner())->GetController(), GetOwner(), UDamageType::StaticClass());
			//DrawDebugLine(GetWorld(), RayStart, ShotHit.ImpactPoint, FColor(0, 255, 0), true, 0, 0, 10);
		}
		if (ProjectileBlueprint)
		{
			AProjectile* PhaserProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, RayStart, MyOwnerMesh->GetSocketRotation(FName(Socket)));
			PhaserProjectile->LaunchProjectile(ProjectileSpeed, GetOwner());
		}
		
		CurrentTotalAmmo--;
	}
	AWeapon::Fire();
}

void APhasersWeapon::AmmoRegen()
{
	CurrentTotalAmmo += FMath::Min(CurrentTotalAmmo += AmmoRegened, MaxAmmo);
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