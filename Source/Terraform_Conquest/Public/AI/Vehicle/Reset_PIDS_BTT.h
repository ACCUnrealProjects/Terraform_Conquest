// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Reset_PIDS_BTT.generated.h"

/**
 * 
 */
UCLASS()
class TERRAFORM_CONQUEST_API UReset_PIDS_BTT : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

private:

protected:

public:

	UReset_PIDS_BTT();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;

	
};
