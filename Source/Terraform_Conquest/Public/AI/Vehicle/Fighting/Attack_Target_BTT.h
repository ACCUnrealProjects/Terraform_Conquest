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

private:
	class AHover_Vehicles* HoverPawn = nullptr;
	class AAI_Hover_Vehicle_Con* HoverAICon = nullptr;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UAttack_Target_BTT();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
