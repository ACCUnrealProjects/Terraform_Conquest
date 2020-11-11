// Alex Chatt Terraform_Conquest 2020

#include "../../Public/Components/Weapon_Controller_Component.h"
#include "../../Public/Weapons/Weapon.h"
#include "Components/SceneComponent.h"

// Sets default values for this component's properties
UWeapon_Controller_Component::UWeapon_Controller_Component()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UWeapon_Controller_Component::BeginPlay()
{
	Super::BeginPlay();

	PlayerInputSetUp();

	SpawnParams.Owner = GetOwner();
	SpawnParams.Instigator = Cast<APawn>(SpawnParams.Owner);

	if (AllGuns.Num() > 0)
	{
		AllGuns.SetNum(AllowedGunTypes.Num(), false);
	}

	MeshToAttachTo = GetOwner()->FindComponentByClass<USceneComponent>();
	for (auto Gun : AllGuns)
	{
		if (Gun)
		{
			Gun->OnAttach(GetOwner(), MeshToAttachTo);
		}
	}
}

void UWeapon_Controller_Component::PlayerInputSetUp()
{
	if (Cast<APawn>(GetOwner())->GetController()->IsLocalPlayerController())
	{
		UInputComponent* PlayerInputComp = GetOwner()->FindComponentByClass<UInputComponent>();
		if (PlayerInputComp)
		{
			PlayerInputComp->BindAction(TEXT("LeftClickAction"), EInputEvent::IE_Pressed, this, &UWeapon_Controller_Component::FireCurrent);
			PlayerInputComp->BindAction(TEXT("RightClickAction"), EInputEvent::IE_Released, this, &UWeapon_Controller_Component::SwitchWeapon);
		}
	}
}

void UWeapon_Controller_Component::SetWeaponSlots(TArray<GunType> WeaponsICanHave)
{
	AllowedGunTypes = WeaponsICanHave;
	AllGuns.Init(nullptr, AllowedGunTypes.Num());
}

void UWeapon_Controller_Component::AddAmmoForGuns(float AmmoPercent)
{
	for (auto Gun : AllGuns)
	{
		if (Gun)
		{ 
			Gun->AddAmmo(AmmoPercent);
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


void UWeapon_Controller_Component::SwitchWeapon()
{
	if (AllGuns.Num() <= 0) { return; }

	bool FinishedLooking = false;
	int32 SearchGunNum = AllGuns.IndexOfByKey(ActiveWeapon);
	int32 CurrentGunIndex = SearchGunNum;

	while (FinishedLooking == false)
	{
		SearchGunNum = FMath::Clamp(SearchGunNum, 0, AllGuns.Num());
		if (SearchGunNum == CurrentGunIndex)
		{
			FinishedLooking = true;
			break;
		}
		else if (AllGuns.IsValidIndex(SearchGunNum) && AllGuns[SearchGunNum])
		{
			FinishedLooking = true;
			break;
			ActiveWeapon->ChangeActiveState(false);
			ActiveWeapon = AllGuns[SearchGunNum];
			ActiveWeapon->ChangeActiveState(true);
		}
		else
		{
			SearchGunNum++;
		}
	}

}

void UWeapon_Controller_Component::SwitchWeapon(GunType GunToLookFor)
{
	if (AllGuns.Num() <= 0) { return; }

	for (auto Gun : AllGuns)
	{
		if (Gun->GetGunType() == GunToLookFor)
		{
			if (ActiveWeapon) 
			{
				ActiveWeapon->ChangeActiveState(false);
			}
			ActiveWeapon = Gun;
			ActiveWeapon->ChangeActiveState(true);
			break;
		}
	}

}

void UWeapon_Controller_Component::AddWeapon(TSubclassOf<AWeapon> NewWeapon)
{
	if (!NewWeapon) { return; }
	AWeapon* NewGun = GetWorld()->SpawnActor<AWeapon>(NewWeapon, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(), SpawnParams);
	NewGun->OnAttach(GetOwner(), MeshToAttachTo);
	int32 GunSlot = 0;
	for (int32 i = 0; i < AllowedGunTypes.Num(); i++)
	{
		if (AllowedGunTypes[i] == NewGun->GetGunType())
		{
			GunSlot = i;
			if (AllGuns[i] != nullptr)
			{
				AllGuns[i]->Destroy();
			}
			break;
		}
	}

	if (AllGuns.IsValidIndex(GunSlot) && AllGuns[GunSlot])
	{
		ActiveWeapon->ChangeActiveState(false);
	}
	AllGuns[GunSlot] = NewGun;
	ActiveWeapon = NewGun;
	ActiveWeapon->ChangeActiveState(true);
}

void UWeapon_Controller_Component::FireCurrent()
{
	if (ActiveWeapon)
	{
		ActiveWeapon->AttemptToFire();
	}
}

AWeapon* UWeapon_Controller_Component::GetCurrentGun() const
{
	return ActiveWeapon;
}

FName UWeapon_Controller_Component::GetWeaponWithIndexName(int32 index) const
{
	if (AllGuns.IsValidIndex(index) && AllGuns[index])
	{
		return AllGuns[index]->GetWeaponName();
	}

	return FName(TEXT(""));
}
