// Alex Chatt Terraform_Conquest 2020


#include "AI/Vehicle/Reset_PIDS_BTT.h"
#include "Controller/AI_Hover_Vehicle_Con.h"
#include "Vehicle/HoverVehicles/Hover_Vehicles.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

UReset_PIDS_BTT::UReset_PIDS_BTT()
{
	NodeName = TEXT("Reset PIDS");
}


EBTNodeResult::Type UReset_PIDS_BTT::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	AAIController* const MyHoverAI = Cast<AAIController>(owner_comp.GetAIOwner());
	if (!MyHoverAI) { return EBTNodeResult::Failed; }
	AHover_Vehicles* MyHoverVehicle = Cast<AHover_Vehicles>(MyHoverAI->GetPawn());
	if (!MyHoverVehicle) { return EBTNodeResult::Failed; }

	MyHoverVehicle->ResetPids();

	return EBTNodeResult::Succeeded;
}
