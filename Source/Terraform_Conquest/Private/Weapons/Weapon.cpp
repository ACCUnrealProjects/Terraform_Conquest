// Alex Chatt Terraform_Conquest 2020

#include "Weapons/Weapon.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values for this component's properties
AWeapon::AWeapon()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;
	bNetLoadOnClient = true;
	SetReplicatingMovement(true);

	WeaponSC = CreateDefaultSubobject<USceneComponent>(TEXT("MySceneComp"));
	SetRootComponent(WeaponSC);

	Tags.Add("Weapon");
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

void AWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Replicate everywhere
	DOREPLIFETIME(AWeapon, WeaponName);
	DOREPLIFETIME(AWeapon, myWeaponType);
	DOREPLIFETIME(AWeapon, TeamId);
	DOREPLIFETIME(AWeapon, CurrentTotalAmmo);
	DOREPLIFETIME(AWeapon, MaxAmmo);

	//Replicate to owner client and server only
	//DOREPLIFETIME_CONDITION(AWeapon, , COND_OwnerOnly);
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

bool AWeapon::Fire_Validate()
{
	return true;
}

void AWeapon::Fire_Implementation()
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
	ServerAttemptToFire();
}

bool AWeapon::ServerAttemptToFire_Validate()
{
	if (GetWorld()->GetRealTimeSeconds() - LastFire < FireRate)
	{
		return false;
	}

	return true;
}

void AWeapon::ServerAttemptToFire_Implementation()
{
	LastFire = GetWorld()->GetRealTimeSeconds();
	if (CurrentTotalAmmo <= 0)
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

void AWeapon::AddExternalAmmo(const float AmmoPercent)
{
	int32 AmmoToAdd = FMath::Floor(MaxAmmo * AmmoPercent);
	AddAmmo(AmmoToAdd);
}

void AWeapon::AmmoRegen()
{
	AddAmmo(AmmoRegened);
}

void AWeapon::AddAmmo(const int32 AmmoAmount)
{
	ServerAddAmmo(AmmoAmount);
}

bool AWeapon::ServerAddAmmo_Validate(const int32 AmmoAmount)
{
	return true;
}

void AWeapon::ServerAddAmmo_Implementation(const int32 AmmoAmount)
{
	CurrentTotalAmmo = FMath::Min(CurrentTotalAmmo + AmmoAmount, MaxAmmo);
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
