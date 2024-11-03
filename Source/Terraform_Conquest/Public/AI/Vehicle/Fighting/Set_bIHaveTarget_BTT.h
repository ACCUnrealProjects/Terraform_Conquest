// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Set_bIHaveTarget_BTT.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TERRAFORM_CONQUEST_API USet_bIHaveTarget_BTT : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	bool bHaveTarget = false;

protected:

public:
	USet_bIHaveTarget_BTT();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;
};
