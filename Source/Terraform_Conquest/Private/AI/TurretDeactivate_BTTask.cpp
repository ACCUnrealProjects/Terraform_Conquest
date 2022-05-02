// Alex Chatt Terraform_Conquest 2020


#include "AI/TurretDeactivate_BTTask.h"
#include "Controller/Turret_Controller.h"
#include "Building/Turret.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

UTurretDeactivate_BTTask::UTurretDeactivate_BTTask()
{
	NodeName = TEXT("Turret Deactivate");
	bNotifyTick = true;
}

EBTNodeResult::Type UTurretDeactivate_BTTask::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	ATurret_Controller* const MyTurretAI = Cast<ATurret_Controller>(owner_comp.GetAIOwner());
	if (!MyTurretAI) { return EBTNodeResult::Failed; }
	ATurret* MyTurret = Cast<ATurret>(MyTurretAI->GetPawn());
	if (!MyTurret) { return EBTNodeResult::Failed; }

	DirectionToFace = MyTurret->GetActorForwardVector() * 0.5f;
	DirectionToFace.Z = 0.5f;
	DirectionToFace = DirectionToFace.GetSafeNormal();

	if (MyTurret->AmILookingAtTargetDir(DirectionToFace))
	{
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::InProgress;
}

void UTurretDeactivate_BTTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	ATurret_Controller* const MyTurretAI = Cast<ATurret_Controller>(OwnerComp.GetAIOwner());
	if (!MyTurretAI) { FinishLatentTask(OwnerComp, EBTNodeResult::Failed); }
	ATurret* MyTurret = Cast<ATurret>(MyTurretAI->GetPawn());
	if (!MyTurret) { FinishLatentTask(OwnerComp, EBTNodeResult::Failed); }

	if (MyTurret->AmILookingAtTargetDir(DirectionToFace))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}