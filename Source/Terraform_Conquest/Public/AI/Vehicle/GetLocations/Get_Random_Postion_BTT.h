// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "UObject/UObjectGlobals.h"
#include "Get_Random_Postion_BTT.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TERRAFORM_CONQUEST_API UGet_Random_Postion_BTT : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowPrivateAccess = "true"))
	float Radius = 15000;

protected:

public:

	UGet_Random_Postion_BTT();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;
};
