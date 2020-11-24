// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Pawn.h"
#include "Building.generated.h"

UCLASS()
class TERRAFORM_CONQUEST_API ABuilding : public APawn
{
	GENERATED_BODY()
	
private:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TilesImOn", meta = (AllowPrivateAccess = "true"))
	TArray<class AMapTile*> TilesImOn;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BuildingMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "OverlapSpace", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BuildOverlapSpace = nullptr;

	FGenericTeamId TeamId;

protected:

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Health")
	class UHealth_Component* MyHealthComp = nullptr;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Sets default values for this actor's properties
	ABuilding();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetTilesImOn(TArray<AMapTile*> BuiltTiles);

	void SetTeamID(FGenericTeamId TeamID);

	FGenericTeamId GetTeamId() const;

	virtual void StartDestroy();

	void DestroyCleanUp();

};
