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

EBTNodeResult::Type UAttack_Target_BTT::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	Super::ExecuteTask(owner_comp, node_memory);

	AAI_Hover_Vehicle_Con* const HoverAICon = Cast<AAI_Hover_Vehicle_Con>(owner_comp.GetAIOwner());
	if (!HoverAICon) { FinishLatentTask(owner_comp, EBTNodeResult::Failed); }
	AHover_Vehicles* const HoverPawn = Cast<AHover_Vehicles>(HoverAICon->GetPawn());
	if (!HoverPawn) { FinishLatentTask(owner_comp, EBTNodeResult::Failed); }
	AActor* const TargetActor = Cast<AActor>(HoverAICon->GetBlackboard()->GetValueAsObject(GetSelectedBlackboardKey()));
	if (!TargetActor) 
	{ 
		FinishLatentTask(owner_comp, EBTNodeResult::Succeeded); 
	}
	else
	{
		auto ActorHealth = TargetActor->FindComponentByClass<UHealth_Component>();
		if (ActorHealth && ActorHealth->AmIDead())
		{
			HoverPawn->StopFiring();
			return EBTNodeResult::Succeeded;
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


	return EBTNodeResult::Succeeded;
}