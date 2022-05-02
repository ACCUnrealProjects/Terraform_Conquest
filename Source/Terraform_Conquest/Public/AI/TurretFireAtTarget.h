// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "TurretFireAtTarget.generated.h"

/**
 * 
 */
UCLASS()
class TERRAFORM_CONQUEST_API UTurretFireAtTarget : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

private:

protected:

public:

	UTurretFireAtTarget();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;
	
};
