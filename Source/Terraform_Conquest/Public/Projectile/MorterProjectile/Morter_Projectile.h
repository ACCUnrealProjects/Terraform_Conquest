// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "Projectile/Projectile.h"
#include "Morter_Projectile.generated.h"

/**
 * 
 */
UCLASS()
class TERRAFORM_CONQUEST_API AMorter_Projectile : public AProjectile
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "ProjectileMovement", meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement = nullptr;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Effects", meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* TrailEffect = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Collision", meta = (AllowPrivateAccess = "true"))
		class UShapeComponent* SphereCollider = nullptr;

private:

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "MorterSpeed")
		float MorterSpeed = 5000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		float DamageRadius = 1.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void HitResponse(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

public:
	// Sets default values for this actor's properties
	AMorter_Projectile();

	virtual void LaunchProjectile() override;
};
