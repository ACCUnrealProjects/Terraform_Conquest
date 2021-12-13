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

	WeaponSC = CreateDefaultSubobject<USceneComponent>(TEXT("MySceneComp"));
	SetRootComponent(WeaponSC);
}

// Called when the game starts
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	ShotParams.AddIgnoredActor(GetOwner());
	ActorParams.Owner = GetOwner();
	ActorParams.Instigator = Cast<APawn>(GetOwner());

	AmmoRegenStartTimerParam.BindUFunction(this, FName("StartRegenAmmo"), false);

	CurrentTotalAmmo = MaxAmmo;
	AmmoRegened = MaxAmmo * AmmoRegenPercentage;
	
	GetTeam();
}

void AWeapon::GetTeam()
{
	if (!GetOwner()) { return; }

	for (auto tag : GetOwner()->Tags)
	{
		for (uint8 i = 0; i < (uint8)ETeam::Last; i++)
		{
			if (GetTeamName(ETeam(i)) == tag.ToString())
			{
				TeamId = ETeam(i);
			}
		}
	}
}

void AWeapon::Fire()
{
	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}
	FireEffect->Activate();

	GetWorld()->GetTimerManager().ClearTimer(AmmoRegenStartTimer);
	if (!ExternalRegenOn)
	{
		GetWorld()->GetTimerManager().ClearTimer(AmmoRegenTimer);
	}
	GetWorld()->GetTimerManager().SetTimer(AmmoRegenStartTimer, AmmoRegenStartTimerParam, TimeTillAmmoRegenStarts, false);
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

void AWeapon::AmmoRegen()
{
	CurrentTotalAmmo = FMath::Min(CurrentTotalAmmo + AmmoRegened, MaxAmmo);
}

void AWeapon::StartRegenAmmo(const bool bExternalTrigger)
{
	ExternalRegenOn = bExternalTrigger;
	if (bExternalTrigger)
	{
		GetWorld()->GetTimerManager().ClearTimer(AmmoRegenTimer);
	}
	GetWorld()->GetTimerManager().SetTimer(AmmoRegenTimer, this, &AWeapon::AmmoRegen, AmmoRegenRate, true);
}

void AWeapon::CancelRegenAmmo()
{
	ExternalRegenOn = false;
	GetWorld()->GetTimerManager().ClearTimer(AmmoRegenTimer);
}

void AWeapon::ChangeActiveState(const bool AmIActive)
{
	if (AmIActive)
	{
		FTimerDelegate TimerParam;
		GetWorld()->GetTimerManager().SetTimer(AmmoRegenStartTimer, AmmoRegenStartTimerParam, TimeTillAmmoRegenStarts, false);
	}
}
