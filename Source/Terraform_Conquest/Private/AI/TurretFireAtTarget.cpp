// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/TurretFireAtTarget.h"
#include "Controller/Turret_Controller.h"
#include "Building/Turret.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

UTurretFireAtTarget::UTurretFireAtTarget()
{
	NodeName = TEXT("Turret Fire At Target");
}


EBTNodeResult::Type UTurretFireAtTarget::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	ATurret_Controller* const MyTurretAI = Cast<ATurret_Controller>(owner_comp.GetAIOwner());
	if (!MyTurretAI) { return EBTNodeResult::Failed; }
	ATurret* MyTurret = Cast<ATurret>(MyTurretAI->GetPawn());
	if (!MyTurret) { return EBTNodeResult::Failed; }

	AActor* TargetActor = Cast<AActor>(MyTurretAI->GetBlackboard()->GetValueAsObject(GetSelectedBlackboardKey()));
	if (!TargetActor) { return EBTNodeResult::Failed; }

	MyTurret->AimAt(TargetActor);

	MyTurret->Fire(TargetActor);

	return EBTNodeResult::Succeeded;
}
