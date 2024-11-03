// Alex Chatt Terraform_Conquest 2020

#include "AI/Vehicle/Hover_MoveTo_BTT.h"
#include "Controller/AI_Hover_Vehicle_Con.h"
#include "Vehicle/HoverVehicles/Hover_Vehicles.h"
#include "Components/Hover_Component.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

UHover_MoveTo_BTT::UHover_MoveTo_BTT()
{
	NodeName = TEXT("Hover Move To");
	bNotifyTick = 1;
}

EBTNodeResult::Type UHover_MoveTo_BTT::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	// Check we have everthing we need for this task
	HoverAICon = Cast<AAI_Hover_Vehicle_Con>(OwnerComp.GetAIOwner());
	if (!HoverAICon) { FinishLatentTask(OwnerComp, EBTNodeResult::Failed); }
	HoverPawn = Cast<AHover_Vehicles>(HoverAICon->GetPawn());
	if (!HoverPawn) { FinishLatentTask(OwnerComp, EBTNodeResult::Failed); }
	HoverComp = HoverPawn->FindComponentByClass<UHover_Component>();
	if (!HoverComp) { FinishLatentTask(OwnerComp, EBTNodeResult::Failed); }

	return EBTNodeResult::InProgress;
}

void UHover_MoveTo_BTT::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	FVector TargetPos;
	if (TargetIsActor)
	{
		UObject* ObjectTarCheck = HoverAICon->GetBlackboard()->GetValueAsObject(GetSelectedBlackboardKey());
		if (Cast<AActor>(ObjectTarCheck) != nullptr)
		{
			TargetPos = Cast<AActor>(ObjectTarCheck)->GetActorLocation();
		}
		else
		{
			Super::FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
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

	return;
}

