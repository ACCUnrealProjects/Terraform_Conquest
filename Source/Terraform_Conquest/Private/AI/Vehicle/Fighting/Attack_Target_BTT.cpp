// Alex Chatt Terraform_Conquest 2020

#include "AI/Vehicle/Fighting/Attack_Target_BTT.h"
#include "Controller/AI_Hover_Vehicle_Con.h"
#include "Vehicle/HoverVehicles/Hover_Vehicles.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/Health_Component.h"

UAttack_Target_BTT::UAttack_Target_BTT()
{
	bNotifyTick = 1;
	NodeName = TEXT("Attack Target");
}


EBTNodeResult::Type UAttack_Target_BTT::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	HoverAICon = Cast<AAI_Hover_Vehicle_Con>(OwnerComp.GetAIOwner());
	if (!HoverAICon) { return EBTNodeResult::Failed; }
	HoverPawn = Cast<AHover_Vehicles>(HoverAICon->GetPawn());
	if (!HoverPawn) { return EBTNodeResult::Failed; }
	return EBTNodeResult::InProgress;
}


void UAttack_Target_BTT::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!HoverAICon || !HoverPawn) 
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return; 
	}

	AActor* const TargetActor = Cast<AActor>(HoverAICon->GetBlackboard()->GetValueAsObject(GetSelectedBlackboardKey()));
	if (!TargetActor) 
	{ 
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	auto ActorHealth = TargetActor->FindComponentByClass<UHealth_Component>();
	if (ActorHealth && ActorHealth->AmIDead())
	{
		HoverPawn->StopFiring();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	HoverPawn->LookAtTarget(TargetActor);
	if (HoverPawn->ShouldIStartShooting(TargetActor->GetActorLocation()))
	{
		HoverPawn->Fire();
	}
	else
	{
		HoverPawn->StopFiring();
	}
}


EBTNodeResult::Type UAttack_Target_BTT::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);
	if (HoverPawn)
	{
		HoverPawn->StopFiring();
	}
	return EBTNodeResult::Aborted;
}
