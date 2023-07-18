// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "Utility/TeamsEnum.h"
#include "Pawns/TeamActionPawn.h"
#include "Building.generated.h"

UCLASS()
class TERRAFORM_CONQUEST_API ABuilding : public ATeamActionPawn
{
	GENERATED_BODY()
	
private:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TilesImOn", meta = (AllowPrivateAccess = "true"))
	TArray<class AMapTile*> TilesImOn;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "OverlapSpace", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BuildOverlapSpace = nullptr;

protected:

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BuildingMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Health")
	class UHealth_Component* MyHealthComp = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	USoundBase* ExplotionSound = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* DeathExplotion = nullptr;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	UFUNCTION()
	virtual void Death();

	void DestroyCleanUp();

public:	

	// Sets default values for this actor's properties
	ABuilding();

	/* Property replication */
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetTilesImOn(TArray<AMapTile*> BuiltTiles);

};
