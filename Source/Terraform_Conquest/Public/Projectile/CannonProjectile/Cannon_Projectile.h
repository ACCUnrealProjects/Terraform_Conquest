// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile/Projectile.h"
#include "Cannon_Projectile.generated.h"

class UParticleSystemComponent;

UCLASS()
class TERRAFORM_CONQUEST_API ACannon_Projectile : public AProjectile
{
	GENERATED_BODY()
	
private:


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float Damage = 10.0f;

	virtual void HitResponse(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

public:	
	// Sets default values for this actor's properties
	ACannon_Projectile();

};
