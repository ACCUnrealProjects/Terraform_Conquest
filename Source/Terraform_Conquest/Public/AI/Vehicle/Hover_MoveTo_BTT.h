// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "Hover_MoveTo_BTT.generated.h"

class AHover_Vehicles;
class AAI_Hover_Vehicle_Con;
class UHover_Component;

/**
 * We have overridden this for hover vehicles as UE4's default move to is very
  "damanding" on the Z axis, which is not great for a hover component
 */
UCLASS(Blueprintable)
class TERRAFORM_CONQUEST_API UHover_MoveTo_BTT : public UBTTask_MoveTo
{
	GENERATED_BODY()

private:
	AHover_Vehicles* HoverPawn = nullptr;
	AAI_Hover_Vehicle_Con* HoverAICon = nullptr;
	UHover_Component* HoverComp = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TargetType", meta = (AllowPrivateAccess = "true"))
	bool TargetIsActor = false;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	UHover_MoveTo_BTT();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
