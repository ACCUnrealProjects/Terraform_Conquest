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

private:

	void Death();

	UFUNCTION()
		void OnRep_SaveHit();

	void SpawnEffect();

protected:

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "multiplayer", meta = (AllowPrivateAccess = "true"))
		bool bClientOnlyProjectile = false;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		float Damage = 10.0f;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Collison", meta = (AllowPrivateAccess = "true"))
		bool HitTarget = false;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Mesh")
		class UStaticMeshComponent* ProjectileMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
		TSubclassOf<class AImpact_Effect> MyImpactEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Death")
		float ProjectileLifeTime = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Death")
		float DestroyTime = 1.0f;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_SaveHit)
		FHitResult SavedHit;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void HitResponse(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) ;

public:	
	// Sets default values for this actor's properties
	AProjectile();

	/** Property replication */
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void SetClientOnlyProjectile();

	virtual void LaunchProjectile() PURE_VIRTUAL( AProjectile::LaunchProjectile, );
};
