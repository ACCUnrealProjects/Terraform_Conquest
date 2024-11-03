// Alex Chatt Terraform_Conquest 2020

#include "AI/Vehicle/Fighting/Set_bIHaveTarget_BTT.h"
#include "Controller/AI_Hover_Vehicle_Con.h"
#include "Vehicle/HoverVehicles/Hover_Vehicles.h"
#include "Components/Hover_Move_Component.h"

USet_bIHaveTarget_BTT::USet_bIHaveTarget_BTT()
{
	NodeName = TEXT("Set I have Target");
}

EBTNodeResult::Type USet_bIHaveTarget_BTT::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	Super::ExecuteTask(owner_comp, node_memory);

	AAIController* const MyHoverAI = Cast<AAIController>(owner_comp.GetAIOwner());
	if (!MyHoverAI) { return EBTNodeResult::Failed; }
	AHover_Vehicles* MyHoverVehicle = Cast<AHover_Vehicles>(MyHoverAI->GetPawn());
	if (!MyHoverVehicle) { return EBTNodeResult::Failed; }

	UHover_Move_Component* MyHoverComp = MyHoverVehicle->FindComponentByClass<UHover_Move_Component>();
	if (MyHoverComp)
	{
		MyHoverComp->SetTargetLook(bHaveTarget);
	}
	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}