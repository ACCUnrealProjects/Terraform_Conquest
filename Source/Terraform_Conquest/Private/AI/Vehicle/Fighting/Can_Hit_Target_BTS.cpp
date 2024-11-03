// Alex Chatt Terraform_Conquest 2020

#include "AI/Vehicle/Fighting/Can_Hit_Target_BTS.h"
#include "Controller/AI_Hover_Vehicle_Con.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Vehicle/HoverVehicles/Hover_Vehicles.h"
#include "BehaviorTree/BehaviorTreeTypes.h"

UCan_Hit_Target_BTS::UCan_Hit_Target_BTS()
{
	bNotifyTick = true;
	NodeName = TEXT("Can I hit Target");
}

void UCan_Hit_Target_BTS::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAI_Hover_Vehicle_Con* const HoverAICon = Cast<AAI_Hover_Vehicle_Con>(OwnerComp.GetAIOwner());
	if (!HoverAICon) { return; }
	AHover_Vehicles* const HoverPawn = Cast<AHover_Vehicles>(HoverAICon->GetPawn());
	if (!HoverPawn) { return; }

	AActor* const TargetActor = Cast<AActor>(HoverAICon->GetBlackboard()->GetValueAsObject(GetSelectedBlackboardKey()));

	if (!TargetActor) { return; }

	if (HoverPawn->CanAimAtTarget(TargetActor->GetActorLocation()))
	{
		HoverAICon->GetBlackboard()->SetValueAsBool(bCanHitTarget.SelectedKeyName, true);
	}
	else
	{
		HoverAICon->GetBlackboard()->SetValueAsBool(bCanHitTarget.SelectedKeyName, false);
	}
}

