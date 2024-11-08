// Alex Chatt Terraform_Conquest 2020


#include "AI/Vehicle/Set_Straf_BTT.h"
#include "Controller/AI_Hover_Vehicle_Con.h"
#include "Vehicle/HoverVehicles/Hover_Vehicles.h"
#include "Components/Hover_Move_Component.h"

USet_Straf_BTT::USet_Straf_BTT()
{
	NodeName = TEXT("Set strafe movement");
}

EBTNodeResult::Type USet_Straf_BTT::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	Super::ExecuteTask(owner_comp, node_memory);

	AAIController* const MyHoverAI = Cast<AAIController>(owner_comp.GetAIOwner());
	if (!MyHoverAI) { return EBTNodeResult::Failed; }
	AHover_Vehicles* MyHoverVehicle = Cast<AHover_Vehicles>(MyHoverAI->GetPawn());
	if (!MyHoverVehicle) { return EBTNodeResult::Failed; }

	UHover_Move_Component* MyHoverComp = MyHoverVehicle->FindComponentByClass<UHover_Move_Component>();
	if (MyHoverComp)
	{
		MyHoverComp->SetAIStrafe(bStrafeMode);
	}
	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
