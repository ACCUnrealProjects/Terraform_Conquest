// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "Combat_AI_Con.generated.h"

/**
 * 
 */
UCLASS()
class TERRAFORM_CONQUEST_API ACombat_AI_Con : public AAIController
{
	GENERATED_BODY()

private:

protected:

	virtual void BeginPlay() override;

	virtual void SetPawn(APawn* const InPawn) override;

	virtual void OnPossess(APawn* const InPawn) override;

	virtual void SetupPerceptionSystem();

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "AI")
	class UBehaviorTreeComponent* BehaviorTreeComp;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "AI")
	class UBehaviorTree* BehaviorTree;

	class UBlackboardComponent* BlackBoardComp;

	class UAISenseConfig_Sight* AISightConfig;

public:

	ACombat_AI_Con();

	class UBlackboardComponent* GetBlackboard() const;
	
};
