// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "Can_Hit_Target_BTS.generated.h"

/**
 * 
 */
UCLASS()
class TERRAFORM_CONQUEST_API UCan_Hit_Target_BTS : public UBTService_BlackboardBase
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	float TimeOut = 60.0f;

	UPROPERTY(EditAnywhere, Category = "Blackboard", meta = (AllowPrivateAccess = "true"))
	struct FBlackboardKeySelector bCanHitTarget;

protected:

public:

	UCan_Hit_Target_BTS();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
