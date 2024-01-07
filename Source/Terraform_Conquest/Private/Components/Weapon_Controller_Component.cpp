// Alex Chatt Terraform_Conquest 2020

#include "Components/Weapon_Controller_Component.h"
#include "Engine/ActorChannel.h"
#include "Weapons/Weapon.h"
#include "Utility/WeaponContainerV2.h"
#include "Net/UnrealNetwork.h"
#include "Components/SceneComponent.h"

// Sets default values for this component's properties
UWeapon_Controller_Component::UWeapon_Controller_Component()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

// Called when the game starts
void UWeapon_Controller_Component::BeginPlay()
{
	Super::BeginPlay();

	SpawnParams.Owner = GetOwner();
	SpawnParams.Instigator = Cast<APawn>(SpawnParams.Owner);
	RayColParams.AddIgnoredActor(GetOwner());

	MeshToAttachTo = GetOwner()->FindComponentByClass<USceneComponent>();
}

void UWeapon_Controller_Component::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Replicate everywhere
	DOREPLIFETIME(UWeapon_Controller_Component, ActiveWeapon);
	DOREPLIFETIME(UWeapon_Controller_Component, AllGuns);

	//Replicate to owner client and server only
	DOREPLIFETIME_CONDITION(UWeapon_Controller_Component, AllowedGunTypes, COND_OwnerOnly);
}

bool UWeapon_Controller_Component::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool bWroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	bWroteSomething |= Channel->ReplicateSubobjectList(AllGuns, *Bunch, *RepFlags);
	bWroteSomething |= Channel->ReplicateSubobject(ActiveWeapon, *Bunch, *RepFlags);

	return bWroteSomething;
}

bool UWeapon_Controller_Component::ServerSetWeaponSlots_Validate(const TArray<GunType> &WeaponsICanHave)
{
	return true;
}

void UWeapon_Controller_Component::ServerSetWeaponSlots_Implementation(const TArray<GunType> &WeaponsICanHave)
{
	AllowedGunTypes = WeaponsICanHave;
}

void UWeapon_Controller_Component::StartRegenForGuns()
{
	for (auto GunSet : AllGuns)
	{
		for (auto Gun : GunSet->WeaponsList)
		{
			Gun->StartRegenAmmo(true);
		}
	}
}

void UWeapon_Controller_Component::StopRegenForGuns()
{
	for (auto GunSet : AllGuns)
	{
		for (auto Gun : GunSet->WeaponsList)
		{
			Gun->CancelRegenAmmo();
		}
	}
}

bool UWeapon_Controller_Component::CanIHaveGunType(GunType NewGunType)
{
	for (auto AllowedGunType : AllowedGunTypes)
	{
		if (AllowedGunType == NewGunType)
		{
			return true;
		}
	}
	return false;
}

void UWeapon_Controller_Component::AddSocketsForWeapons(GunType WeaponType, TArray<FName> SlotNames)
{
	for (auto WeaponSlots : WeaponSlotsList)
	{
		if (WeaponSlots.WeaponsType == WeaponType)
		{
			WeaponSlots.WeaponSlots = SlotNames;
			return;
		}
	}

	FWeaponSlotList NewSlots;
	NewSlots.WeaponSlots = SlotNames;
	NewSlots.WeaponsType = WeaponType;
	WeaponSlotsList.Add(NewSlots);
}

void UWeapon_Controller_Component::SwitchWeapon()
{
	// If we only have 1 gun then we cant really switch to another
	if (AllGuns.Num() <= 1) { return; }

	bool bFinishedLooking = false;
	uint8 SearchGunNum = 0, CurrectGunNum = 0;

	if (ActiveWeapon && (uint8)ActiveWeapon->WeaponsType)
	{ 
		CurrectGunNum = SearchGunNum = (uint8)ActiveWeapon->WeaponsType;
	}

	while (!bFinishedLooking)
	{
		SearchGunNum++;
		if (SearchGunNum >= (uint8)GunType::End) { (uint8)GunType::None + 1; }
		//We have looped back to our original weapon, so nothing to switch to
		if (SearchGunNum == CurrectGunNum) 
		{ 
			bFinishedLooking = true;
			break; 
		}
		for (auto GunSet : AllGuns)
		{
			if (GunSet->WeaponsType == (GunType)SearchGunNum)
			{
				bFinishedLooking = true;
				ServerChangeWeapon((GunType)SearchGunNum);
				break;
			}
		}
	}
}

void UWeapon_Controller_Component::SwitchWeapon(GunType GunToLookFor)
{
	if (AllGuns.Num() <= 0) { return; }

	for (auto GunSet : AllGuns)
	{
		if (GunSet->WeaponsType == GunToLookFor)
		{
			ServerChangeWeapon(GunToLookFor);
		}
	}
}

bool UWeapon_Controller_Component::ServerChangeWeapon_Validate(GunType NewWeapon)
{
	if (NewWeapon == GunType::None) { return false; }

	return true;
}

void UWeapon_Controller_Component::ServerChangeWeapon_Implementation(GunType NewWeapon)
{
	for (auto GunSet : AllGuns)
	{
		if (GunSet->WeaponsType == NewWeapon)
		{
			if (ActiveWeapon)
			{
				ActiveWeapon->ChangeActiveStateOfGuns(false);
			}
			ActiveWeapon = GunSet;
			ActiveWeapon->ChangeActiveStateOfGuns(true);
			return;
		}
	}
}

void UWeapon_Controller_Component::AddWeapon(TSubclassOf<AWeapon> NewWeapon, GunType WeaponType)
{
	ServerAddWeapon(NewWeapon, WeaponType);
	ServerChangeWeapon(WeaponType);
}

bool UWeapon_Controller_Component::ServerAddWeapon_Validate(TSubclassOf<AWeapon> NewWeapon, GunType WeaponType)
{
	return true;
}

void UWeapon_Controller_Component::ServerAddWeapon_Implementation(TSubclassOf<AWeapon> NewWeapon, GunType WeaponType)
{
	if (!NewWeapon || !CanIHaveGunType(WeaponType)) { return; }

	bool bHaveGunType = false;
	UWeaponContainerV2* WeaponSet = nullptr;

	for (int32 i = 0; i < AllowedGunTypes.Num(); i++)
	{
		if (AllowedGunTypes[i] == WeaponType)
		{
			for (auto GunSet : AllGuns)
			{
				if (GunSet->WeaponsType == WeaponType)
				{
					WeaponSet = GunSet;
					bHaveGunType = true;
					for (int32 j = 0; j < GunSet->WeaponsList.Num(); j++)
					{
						GunSet->WeaponsList[j]->Destroy();
					}
					GunSet->WeaponsList.Empty();
				}
			}
			break;
		}
	}
	
	if (!bHaveGunType)
	{
		UWeaponContainerV2* NewWeaponSet = NewObject<UWeaponContainerV2>(this, UWeaponContainerV2::StaticClass());
		NewWeaponSet->WeaponsType = WeaponType;
		WeaponSet = NewWeaponSet;
		AllGuns.Add(NewWeaponSet);
	}

	for (auto WeaponSlots : WeaponSlotsList)
	{
		if (WeaponSlots.WeaponsType == WeaponType)
		{
			for (auto WeaponSocket : WeaponSlots.WeaponSlots)
			{
				AWeapon* NewGun = GetWorld()->SpawnActor<AWeapon>(NewWeapon, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(), SpawnParams);
				NewGun->AttachToActor(GetOwner(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), WeaponSocket);
				NewGun->ChangeActiveState(true);
				WeaponSet->WeaponsList.Add(NewGun);
			}
			break;
		}
	}

	if (ActiveWeapon)
	{
		ActiveWeapon->ChangeActiveStateOfGuns(false);
	}
	ActiveWeapon = WeaponSet;
	ActiveWeapon->ChangeActiveStateOfGuns(true);
}

void UWeapon_Controller_Component::FireCurrent()
{
	if (!ActiveWeapon) { return; }

	for (auto Gun : ActiveWeapon->WeaponsList)
	{
		Gun->Fire();
	}
}

bool UWeapon_Controller_Component::ServerRotateCurrentWeapons_Validate(FVector CamPos, FVector CamDirection)
{
	return true;
}

void UWeapon_Controller_Component::ServerRotateCurrentWeapons_Implementation(FVector CamPos, FVector CamDirection)
{
	if (!ActiveWeapon || ActiveWeapon->WeaponsType == GunType::Mine) { return; }

	for (auto Gun : ActiveWeapon->WeaponsList)
	{
		FHitResult RayHit;
		FVector RayEnd = CamPos + (CamDirection * Gun->GetRange());
		FVector AimPosition = RayEnd;
		if (GetWorld()->LineTraceSingleByChannel(RayHit, CamPos, RayEnd, ECollisionChannel::ECC_Camera, RayColParams))
		{
			AimPosition = RayHit.ImpactPoint;
		}
		FVector AimDir = (AimPosition - Gun->GetActorLocation()).GetSafeNormal();
		FRotator RotationChange = AimDir.Rotation() - Gun->GetActorForwardVector().Rotation();
		Gun->AddActorLocalRotation(FRotator(RotationChange.Pitch, RotationChange.Yaw, 0));
	}
}

TArray<AWeapon*> UWeapon_Controller_Component::GetCurrentGuns() const
{
	if (!ActiveWeapon)
	{
		return TArray<AWeapon*>();
	}

	return ActiveWeapon->WeaponsList;
}

FName UWeapon_Controller_Component::GetWeaponNameOfGunType(GunType GunType) const
{
	for (auto GunSet : AllGuns)
	{
		if (GunSet 
			&& GunSet->WeaponsType == GunType 
			&& GunSet->WeaponsList.Num() > 0)
		{
			if (GunSet->WeaponsList[0])
			{
				return GunSet->WeaponsList[0]->GetWeaponName();
			} 
		}
	}

	return FName(TEXT("N/A"));
}
