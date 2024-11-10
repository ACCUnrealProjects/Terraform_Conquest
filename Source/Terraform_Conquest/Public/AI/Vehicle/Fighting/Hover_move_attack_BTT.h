// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "Hover_move_attack_BTT.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TERRAFORM_CONQUEST_API UHover_move_attack_BTT : public UBTTask_MoveTo
{
	GENERATED_BODY()

private:
	class AHover_Vehicles* HoverPawn = nullptr;
	class AAI_Hover_Vehicle_Con* HoverAICon = nullptr;
	class UHover_Component* HoverComp = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TargetType", meta = (AllowPrivateAccess = "true"))
	bool bTargetIsActor = false;

	UPROPERTY(EditAnywhere, Category = "Blackboard", meta = (AllowPrivateAccess = "true"))
	struct FBlackboardKeySelector TargetKey;

	void MoveZCheck(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	void Attack(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;

public:
	UHover_move_attack_BTT();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	
};
