//Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Health_Component.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FActorHasDied);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TERRAFORM_CONQUEST_API UHealth_Component : public UActorComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthSetUp", meta = (AllowPrivateAccess = "true"))
		int32 MaxHealth = 100;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "HealthSetUp", meta = (AllowPrivateAccess = "true"))
		int32 Health = MaxHealth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShieldSetUp", meta = (AllowPrivateAccess = "true"))
		int32 MaxShield = 100;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "ShieldSetUp", meta = (AllowPrivateAccess = "true"))
		int32 Shield = MaxShield;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ShieldRegenSetUp", meta = (AllowPrivateAccess = "true"))
		float ShieldRegenRate = 0.5f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ShieldRegenSetUp", meta = (AllowPrivateAccess = "true"))
		float ShieldRegenPerTick = 2.5f;
	bool SheildRegenOn = false;

	float TimeBeforeShieldRegenBegins = 5.0f;
	float TimeSinceLastHit = 5.0f;
	
	FTimerHandle SheildRegenTickTimer;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	UHealth_Component();

	virtual void PostInitProperties() override;

	/** Property replication */
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
		void SheildRegenTick();

	void SetUp(int32 StartHealth, int32 StartShield);
	UFUNCTION(reliable, server, WithValidation)
		void ServerSetUp(int32 StartHealth, int32 StartShield);

	void IncreaseHealth(int32 HealthIncrease);
	UFUNCTION(Unreliable, server, WithValidation)
		void ServerIncreaseHealth(int32 HealthIncrease);

	void IncreaseShield(int32 ShieldIncrease);
	UFUNCTION(Unreliable, server, WithValidation)
		void ServerIncreaseShield(int32 ShieldIncrease);

	bool AmIAtMaxHealthAndShield() const;
	bool AmIDead() const;

	UFUNCTION(reliable, server, WithValidation)
		void ServerKillMe();

	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealthPercentage() const;
	UFUNCTION(BlueprintPure, Category = "Shield")
		float GetShieldPercentage() const;

    float TakeDamage(float Damage);

	FActorHasDied IHaveDied;
};
