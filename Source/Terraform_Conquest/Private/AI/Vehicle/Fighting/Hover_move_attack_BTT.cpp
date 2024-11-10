// Alex Chatt Terraform_Conquest 2020

#include "AI/Vehicle/Fighting/Hover_move_attack_BTT.h"
#include "Controller/AI_Hover_Vehicle_Con.h"
#include "Vehicle/HoverVehicles/Hover_Vehicles.h"
#include "Components/Hover_Component.h"
#include "Components/Health_Component.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

UHover_move_attack_BTT::UHover_move_attack_BTT()
{
	NodeName = TEXT("Hover move and attack");
	bNotifyTick = 1;
	bReachTestIncludesGoalRadius = bReachTestIncludesAgentRadius = true;
}

EBTNodeResult::Type UHover_move_attack_BTT::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	// Check we have everthing we need for this task
	HoverAICon = Cast<AAI_Hover_Vehicle_Con>(OwnerComp.GetAIOwner());
	if (!HoverAICon) { return EBTNodeResult::Failed; }
	HoverPawn = Cast<AHover_Vehicles>(HoverAICon->GetPawn());
	if (!HoverPawn) { return EBTNodeResult::Failed; }
	HoverComp = HoverPawn->FindComponentByClass<UHover_Component>();
	if (!HoverComp) { return EBTNodeResult::Failed; }

	return EBTNodeResult::InProgress;
}

void UHover_move_attack_BTT::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	MoveZCheck(OwnerComp, NodeMemory);
	Attack(OwnerComp, NodeMemory);
}

void UHover_move_attack_BTT::MoveZCheck(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FVector TargetPos;
	if (bTargetIsActor)
	{
		UObject* ObjectTarCheck = HoverAICon->GetBlackboard()->GetValueAsObject(GetSelectedBlackboardKey());
		if (Cast<AActor>(ObjectTarCheck) != nullptr)
		{
			TargetPos = Cast<AActor>(ObjectTarCheck)->GetActorLocation();
		}
		else
		{
			Super::FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			return;
		}
	}
	else
	{
		TargetPos = HoverAICon->GetBlackboard()->GetValueAsVector(GetSelectedBlackboardKey());
	}

	float Distance = FMath::Abs(FVector::Distance(TargetPos, HoverPawn->GetActorLocation()));
	if (Distance < AcceptableRadius)
	{
		float UpDiff = FMath::Abs(TargetPos.Z - HoverPawn->GetActorLocation().Z);
		if (UpDiff < HoverComp->GetHoverLenght())
		{
			//Cancel the pathfinding movement but return success
			//used to compensate for the hover z offset
			AbortTask(OwnerComp, NodeMemory);
			Super::FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
}

void UHover_move_attack_BTT::Attack(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AActor* const TargetActor = Cast<AActor>(HoverAICon->GetBlackboard()->GetValueAsObject(TargetKey.SelectedKeyName));
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

EBTNodeResult::Type UHover_move_attack_BTT::AbortTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	if (HoverPawn)
	{
		HoverPawn->StopFiring();
	}
	return EBTNodeResult::Aborted;
}
