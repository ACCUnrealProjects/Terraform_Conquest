// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "Controller/Combat_AI_Con.h"
#include "AI_Hover_Vehicle_Con.generated.h"

/**
 * 
 */
UCLASS()
class TERRAFORM_CONQUEST_API AAI_Hover_Vehicle_Con : public ACombat_AI_Con
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

	AAI_Hover_Vehicle_Con();

	//virtual void Tick(float DeltaTime) override;

};
