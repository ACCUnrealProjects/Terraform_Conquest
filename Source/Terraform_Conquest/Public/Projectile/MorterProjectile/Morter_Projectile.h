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


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float Damage = 10.0f;

	float DamageRadius;

	virtual void HitResponse(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

public:
	// Sets default values for this actor's properties
	AMorter_Projectile();


};
