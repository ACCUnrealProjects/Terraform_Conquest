//Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Health_Component.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FActorHasDied);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FActorBeenHit);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TERRAFORM_CONQUEST_API UHealth_Component : public UActorComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HealthSetUp", meta = (AllowPrivateAccess = "true"))
		int32 MaxHealth = 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HealthSetUp", meta = (AllowPrivateAccess = "true"))
		int32 Health = MaxHealth;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	UHealth_Component();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetMaxHealth(int32 StartHealth);

	void IncreaseHealth(int32 HealthIncrease);

	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealthPercentage() const;

	bool AmIAtMaxHealth() const;

	bool AmIDead() const;

	void KillMe();

	UFUNCTION()
		void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	FActorHasDied IHaveDied;

	FActorBeenHit IHaveBeenHit;
		
};
