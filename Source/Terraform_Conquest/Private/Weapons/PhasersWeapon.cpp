// Alex Chatt Terraform_Conquest 2020


#include "../../Public/Weapons/PhasersWeapon.h"
#include "Particles/ParticleSystemComponent.h"

APhasersWeapon::APhasersWeapon()
{
	myWeaponType = GunType::Phasers;

	UParticleSystemComponent* PhasersEffect1 = CreateDefaultSubobject<UParticleSystemComponent>(FName(TEXT("Phasers Fire Effect 1")));
	PhasersEffect1->bAutoActivate = false;
	FireEffect.Add(PhasersEffect1);

	UParticleSystemComponent* PhasersEffect2 = CreateDefaultSubobject<UParticleSystemComponent>(FName(TEXT("Phasers Fire Effect 2")));
	PhasersEffect2->bAutoActivate = false;
	FireEffect.Add(PhasersEffect2);
}

void APhasersWeapon::BeginPlay()
{

}

void APhasersWeapon::Fire()
{
	//Raycast fire, also fire projectile flash or laser 

}

void APhasersWeapon::AmmoRegen()
{
	CurrentTotalAmmo += FMath::Min(CurrentTotalAmmo += AmmoRegened, MaxAmmo);
}

void APhasersWeapon::ChangeActiveState(const bool AmIActive)
{
	if (AmIActive)
	{
		GetWorld()->GetTimerManager().SetTimer(AmmoRegenTimer, this, &APhasersWeapon::AmmoRegen, AmmoRegened, false);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(AmmoRegenTimer);
	}
}

void APhasersWeapon::OnAttach(AActor* MyOwner, USceneComponent* OwnerMesh)
{
	if (OwnerMesh)
	{
		FireEffect[0]->AttachToComponent(OwnerMesh, FAttachmentTransformRules::KeepRelativeTransform, FName(FireSocket1));
		FireEffect[1]->AttachToComponent(OwnerMesh, FAttachmentTransformRules::KeepRelativeTransform, FName(FireSocket2));
	}
}