// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "Controller/Combat_AI_Con.h"
#include "Turret_Controller.generated.h"

/**
 * 
 */
UCLASS()
class TERRAFORM_CONQUEST_API ATurret_Controller : public ACombat_AI_Con
{
	GENERATED_BODY()
	
private:

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void PawnHasDiedListener();

	virtual void SetPawn(APawn* const InPawn) override;

	virtual void OnPossess(APawn* const InPawn) override;

	UFUNCTION()
	void OnTargetDetected(AActor* actor, FAIStimulus const stimulus);

	virtual void SetupPerceptionSystem() override;

public:

	ATurret_Controller();

	//virtual void Tick(float DeltaTime) override;
};
