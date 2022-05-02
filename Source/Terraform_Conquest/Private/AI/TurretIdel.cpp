// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TurretIdel.h"
#include "Controller/Turret_Controller.h"
#include "Building/Turret.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

UTurretIdel::UTurretIdel()
{
	NodeName = TEXT("Turret Idel");
	bNotifyTick = true;
	rand.GenerateNewSeed();
}

EBTNodeResult::Type UTurretIdel::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	ATurret_Controller* const MyTurretAI = Cast<ATurret_Controller>(owner_comp.GetAIOwner());
	if (!MyTurretAI) { return EBTNodeResult::Failed; }
	ATurret* MyTurret = Cast<ATurret>(MyTurretAI->GetPawn());
	if (!MyTurret) { return EBTNodeResult::Failed; }

	DirectionToRace.X = rand.FRandRange(-1, 1);
	DirectionToRace.Y = rand.FRandRange(-1, 1);
	DirectionToRace *= 1000;
	DirectionToRace = DirectionToRace.GetSafeNormal();
	
	if (MyTurret->AmILookingAtTargetDir(DirectionToRace))
	{
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::InProgress;
}

void UTurretIdel::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	ATurret_Controller* const MyTurretAI = Cast<ATurret_Controller>(OwnerComp.GetAIOwner());
	if(!MyTurretAI) { FinishLatentTask(OwnerComp, EBTNodeResult::Failed); }
	ATurret* MyTurret = Cast<ATurret>(MyTurretAI->GetPawn());
	if (!MyTurret) { FinishLatentTask(OwnerComp, EBTNodeResult::Failed); }

	if (MyTurret->AmILookingAtTargetDir(DirectionToRace))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
