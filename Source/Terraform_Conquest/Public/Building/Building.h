// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Building.generated.h"

UCLASS()
class TERRAFORM_CONQUEST_API ABuilding : public APawn
{
	GENERATED_BODY()
	
private:	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Sets default values for this actor's properties
	ABuilding();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
