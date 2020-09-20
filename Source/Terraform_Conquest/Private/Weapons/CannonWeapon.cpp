// Alex Chatt Terraform_Conquest 2020


#include "../../Public/Weapons/CannonWeapon.h"
#include "Particles/ParticleSystemComponent.h"

ACannonWeapon::ACannonWeapon()
{
	myWeaponType = GunType::Cannon;

	UParticleSystemComponent *CannonEffect = CreateDefaultSubobject<UParticleSystemComponent>(FName("Cannon Fire Effect"));
	CannonEffect->bAutoActivate = false;
	FireEffect.Add(CannonEffect);
}

void ACannonWeapon::BeginPlay()
{

}

void ACannonWeapon::Fire()
{
	//Fire Projectile
}

void ACannonWeapon::AmmoRegen()
{
	CurrentTotalAmmo += FMath::Min(CurrentTotalAmmo += AmmoRegened, MaxAmmo);
}

void ACannonWeapon::ChangeActiveState(const bool AmIActive)
{
	if (AmIActive)
	{
		GetWorld()->GetTimerManager().SetTimer(AmmoRegenTimer, this, &ACannonWeapon::AmmoRegen, AmmoRegened, false);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(AmmoRegenTimer);
	}
}

void ACannonWeapon::OnAttach(AActor* MyOwner, USceneComponent* OwnerMesh)
{
	if (OwnerMesh)
	{
		FireEffect[0]->AttachToComponent(OwnerMesh, FAttachmentTransformRules::KeepRelativeTransform, FName(FireSocket1));
	}
}