// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "TurretDeactivate_BTTask.generated.h"

/**
 * 
 */
UCLASS()
class TERRAFORM_CONQUEST_API UTurretDeactivate_BTTask : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

private:

	FVector DirectionToFace;

protected:

public:

	UTurretDeactivate_BTTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
