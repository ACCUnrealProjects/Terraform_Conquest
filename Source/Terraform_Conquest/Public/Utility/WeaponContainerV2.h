// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WeaponTypeEnum.h"
#include "WeaponContainerV2.generated.h"

/**
 * 
 */
UCLASS()
class TERRAFORM_CONQUEST_API UWeaponContainerV2 : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "WeaponsType")
		GunType WeaponsType;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "WeaponsList")
		TArray<class AWeapon*> WeaponsList;

	UPROPERTY(Replicated)
		uint32 bReplicatedFlag : 1;

public:

	UWeaponContainerV2();

	virtual bool IsSupportedForNetworking() const override { return true; }

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void ChangeActiveStateOfGuns(const bool bAmActive);
	
};
