// Alex Chatt Terraform_Conquest 2020

#include "Weapons/Weapon.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/TeamActionPawn.h"
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

	if (HasAuthority())
	{
		ShotParams.AddIgnoredActor(GetOwner());
		ActorParams.Owner = this;
		ActorParams.Instigator = Cast<APawn>(GetOwner());
		AmmoRegenStartTimerParam.BindUFunction(this, FName("StartRegenAmmo"), false);
		CurrentTotalAmmo = MaxAmmo;
		AmmoRegened = MaxAmmo * AmmoRegenPercentage;
		GetTeam();
	}
}

void AWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Replicate everywhere
	DOREPLIFETIME(AWeapon, WeaponName);
	DOREPLIFETIME(AWeapon, myWeaponType);
	DOREPLIFETIME(AWeapon, CurrentTotalAmmo);
	DOREPLIFETIME(AWeapon, MaxAmmo);

	//Replicate to owner client and server only
	//DOREPLIFETIME_CONDITION(AWeapon, , COND_OwnerOnly);
}

void AWeapon::GetTeam()
{
	if (!GetOwner()) { return; }

	auto TeamPawn = Cast<ATeamActionPawn>(GetOwner());
	if (TeamPawn)
	{
		TeamId = TeamPawn->GetTeamId();
	}
}

void AWeapon::Fire()
{
	if (CurrentTotalAmmo <= 0)
	{
		if (DryClipSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, DryClipSound, GetActorLocation());
			return;
		}
	}

	if (GetWorld()->GetRealTimeSeconds() - LastFire < FireRate)
	{
		return;
	}
	ServerFire();
	// if we are not the server/stand alone, fire a shot for just the player client
	if (!HasAuthority())
	{
		FireWeapon(true);
	}
	LastFire = GetWorld()->GetRealTimeSeconds();

	CurrentTotalAmmo--;
	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}
	if (FireEffect)
	{
		FireEffect->Activate();
	}
}

bool AWeapon::ServerFire_Validate()
{
	return true;
}

void AWeapon::ServerFire_Implementation()
{
	if (CurrentTotalAmmo <= 0)
	{
		MRPC_PlaySound(GetActorLocation(), DryClipSound, true);
		return;
	}
	else
	{
		if (GetWorld()->GetRealTimeSeconds() - LastFire < (FireRate/2.0f))
		{
			return;
		}
		LastFire = GetWorld()->GetRealTimeSeconds();

		MRPC_PlaySound(GetActorLocation(), FireSound, true);
		MRPC_PlayEffect(FireEffect, true);
		FireWeapon(false);

		GetWorld()->GetTimerManager().ClearTimer(AmmoRegenStartTimer);
		if (!ExternalRegenOn)
		{
			GetWorld()->GetTimerManager().ClearTimer(AmmoRegenTimer);
		}
		GetWorld()->GetTimerManager().SetTimer(AmmoRegenStartTimer, AmmoRegenStartTimerParam, TimeTillAmmoRegenStarts, false);
	}
}

void AWeapon::MRPC_PlaySound_Implementation(FVector SoundLocation, USoundBase* Sound, bool bDontPlayForOwner)
{
	if (bDontPlayForOwner && GetInstigatorController() && 
		GetInstigatorController()->IsLocalController())
	{
		return;
	}

	if (Sound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, Sound, SoundLocation);
	}
}

void AWeapon::MRPC_PlayEffect_Implementation(UParticleSystemComponent* Effect, bool bDontPlayForOwner)
{
	if (bDontPlayForOwner && GetInstigatorController() &&
		GetInstigatorController()->IsLocalController())
	{
		return;
	}

	if (Effect)
	{
		Effect->Activate();
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
		GetWorld()->GetTimerManager().SetTimer(AmmoRegenStartTimer, AmmoRegenStartTimerParam, TimeTillAmmoRegenStarts, false);
	}
}
