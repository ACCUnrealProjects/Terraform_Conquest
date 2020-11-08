// Alex Chatt Terraform_Conquest 2020

#include "../../Public/Weapons/Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values for this component's properties
AWeapon::AWeapon()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	CurrentTotalAmmo = MaxAmmo;
}

void AWeapon::Fire()
{
	if (FireSound)
	{
		for (auto Socket : FireSockets)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, MyOwnerMesh->GetSocketLocation(FName(Socket)));
		}
	}

	for (int i = 0; i < FireEffect.Num(); i++)
	{
		FireEffect[i]->Activate();
	}
}

void AWeapon::AttemptToFire()
{
	if (GetWorld()->GetRealTimeSeconds() - LastFire >= FireRate)
	{
		LastFire = GetWorld()->GetRealTimeSeconds();
		if  (CurrentTotalAmmo <= 0)
		{
			if (DryClipSound)
			{
				UGameplayStatics::PlaySoundAtLocation(this, DryClipSound, GetActorLocation());
			}
			return;
		}
		else if (CurrentTotalAmmo > 0)
		{
			Fire();
			return;
		}
	} 
}

void AWeapon::OnAttach(AActor* MyOwner, USceneComponent* OwnerMesh)
{
	SetOwner(MyOwner);
	ShotParams.AddIgnoredActor(MyOwner);
	MyOwnerMesh = OwnerMesh;
}

void AWeapon::ExternalRegenAmmo()
{
	ExternalRegenOn = true;
	GetWorld()->GetTimerManager().SetTimer(AmmoRegenTimer, this, &AWeapon::AmmoRegen, AmmoRegened, true);
}

void AWeapon::CancelRegenAmmo()
{
	ExternalRegenOn = false;
	GetWorld()->GetTimerManager().ClearTimer(AmmoRegenTimer);
}

bool AWeapon::OutOfAmmo() const
{
	return CurrentTotalAmmo <= 0;
}

void AWeapon::AddAmmo(const float AmmoPercent)
{
	CurrentTotalAmmo = FMath::Min(CurrentTotalAmmo + (int32)(MaxAmmo * AmmoPercent), MaxAmmo);
}

GunType AWeapon::GetGunType() const
{
	return myWeaponType;
}

FName AWeapon::GetWeaponName() const
{
	return WeaponName;
}