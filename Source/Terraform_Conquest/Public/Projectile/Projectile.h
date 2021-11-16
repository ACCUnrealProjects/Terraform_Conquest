// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TERRAFORM_CONQUEST_API AProjectile : public AActor
{
	GENERATED_BODY()
	
private:

	FTimerHandle LifeTimer;

	FTimerHandle DeathTimer;

private:

	void Death();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		float Damage = 10.0f;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Effects", meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* ImpactBlast = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Death")
		float ProjectileLifeTime = 4.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Death")
		float DeathTime = 4.0f;

	AActor* WhoShotMe;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void HitResponse(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Sets default values for this actor's properties
	AProjectile();

	virtual void LaunchProjectile(AActor* Shooter);

};
