// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "TurretIdel.generated.h"

/**
 * 
 */
UCLASS()
class TERRAFORM_CONQUEST_API UTurretIdel : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
private:

	FVector DirectionToRace = FVector(1.0f,0.0f,0.0f);

	FRandomStream rand;

protected:

public:

	UTurretIdel();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
