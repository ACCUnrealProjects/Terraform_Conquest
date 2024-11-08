// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "Look_For_Target_BTS.generated.h"

/**
 * 
 */
UCLASS()
class TERRAFORM_CONQUEST_API ULook_For_Target_BTS : public UBTService_BlackboardBase
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, Category = "Blackboard", meta = (AllowPrivateAccess = "true"))
	struct FBlackboardKeySelector CanSeeTargetBool;

public:

	ULook_For_Target_BTS();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
