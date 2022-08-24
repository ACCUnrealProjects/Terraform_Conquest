// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utility/ProjectileHelp.h"
#include "Impact_Effect.generated.h"

UCLASS()
class TERRAFORM_CONQUEST_API AImpact_Effect : public AActor
{
	GENERATED_BODY()

private:

protected:

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "LifeTime", meta = (AllowPrivateAccess = "true"))
	    float EffectLifeTime = 1.0f;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Effects", meta = (AllowPrivateAccess = "true"))
		class UParticleSystem* ImpactBlast = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Decal")
		FDecalInfo DecalInfo;

	/** default impact sound used when material specific override doesn't exist */
	UPROPERTY(EditDefaultsOnly, Category = Defaults)
		class USoundBase* DefaultSound;

	FHitResult HitInfo;

public:	

private:

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	AImpact_Effect();

	void Set_HitResult(FHitResult hInfo)
	{
		HitInfo = hInfo;
	}

};
