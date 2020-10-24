// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildingBluePrint.generated.h"

UCLASS()
class TERRAFORM_CONQUEST_API ABuildingBluePrint : public AActor
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BuildingProtoTypeMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "OverlapSpace", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* OverlapSpace = nullptr;

protected:

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "TileData")
	TSubclassOf<class ABuilding> BuildingToBuild;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	ABuildingBluePrint();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
