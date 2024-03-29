// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "Actor/TeamActionActor.h"
#include "Mine.generated.h"

UCLASS()
class TERRAFORM_CONQUEST_API AMine : public ATeamActionActor
{
	GENERATED_BODY()
	
private:	

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* TriggerSphere;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* MineMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* ActivateEffect = nullptr;

protected:

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Health")
	class UHealth_Component* MyHealthComp = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Activation")
	float ActivationTime = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Damage")
	float TriggerRadius = 1.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Damage")
	float Damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Death")
	float LifeTime = 1.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Death")
	float DestroyTime = 1.0f;

private:

	UFUNCTION()
	void Death();

	void DestoryMe();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void ActivateMine();

	virtual void Trigger();

public:	
	// Sets default values for this actor's properties
	AMine();

	UFUNCTION()
	void MineOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
