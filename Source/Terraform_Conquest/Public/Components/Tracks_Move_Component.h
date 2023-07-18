// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "Utility/PID_Controller.h"
#include "Tracks_Move_Component.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TERRAFORM_CONQUEST_API UTracks_Move_Component : public UNavMovementComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float EngineThrust = 500000.0f;
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float BackwardsEngineThrust = EngineThrust * 0.3f;

	// PID controllers for AI Rotation/Movement
	PID_Controller MovementPid;
	PID_Controller RotationPid;

private:

	void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Sets default values for this component's properties
	UTracks_Move_Component();

	//Movement
	void Forward(float Amount);
	void Turn(float Amount);

	void SetEngineSpeed(float NewEngineTrust);

};
