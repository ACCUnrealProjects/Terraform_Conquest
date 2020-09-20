// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Vehicle.generated.h"

UCLASS()
class TERRAFORM_CONQUEST_API AVehicle : public APawn
{
	GENERATED_BODY()

private:

protected:
	
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Health")
	class UHealth_Component* MyHealth = nullptr;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* MyMesh = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* FPSCamera = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* TPSCamera = nullptr;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this pawn's properties
	AVehicle();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
