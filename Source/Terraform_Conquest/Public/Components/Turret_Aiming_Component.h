//Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Turret_Aiming_Component.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TERRAFORM_CONQUEST_API UTurret_Aiming_Component : public UActorComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(Replicated)
	class UTurret_Mesh* ActorTurretMesh = nullptr;
	UPROPERTY(Replicated)
	class UBarrel_Mesh* ActorBarrelMesh = nullptr;

	UPROPERTY(Replicated, EditDefaultsOnly, Category = "AimingShot", meta = (AllowPrivateAccess = "true"))
		float DegreesCloseToShot = 5.0f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	UTurret_Aiming_Component();

	void SetUp(class UTurret_Mesh* MyTurret, class UBarrel_Mesh* MyBarrel);

	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const;

	void AimToTarget(FVector TargetPosition);
	UFUNCTION(reliable, server, WithValidation)
	void ServerAimToTarget(FVector TargetPosition);
	virtual bool ServerAimToTarget_Validate(FVector TargetPosition);
	virtual void ServerAimToTarget_Implementation(FVector TargetPosition);

	bool CloseToHittingTarget(FVector TargetPosition);
};
