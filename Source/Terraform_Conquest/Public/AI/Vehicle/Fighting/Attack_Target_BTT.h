// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Attack_Target_BTT.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TERRAFORM_CONQUEST_API UAttack_Target_BTT : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

protected:

public:
	UAttack_Target_BTT();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;
};
