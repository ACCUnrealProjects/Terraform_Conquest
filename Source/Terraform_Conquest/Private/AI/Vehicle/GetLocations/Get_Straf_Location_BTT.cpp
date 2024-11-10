// Alex Chatt Terraform_Conquest 2020

#include "AI/Vehicle/GetLocations/Get_Straf_Location_BTT.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "NavigationSystem.h"

#include "Controller/Combat_AI_Con.h"
#include "Vehicle/Vehicle.h"

UGet_Straf_Location_BTT::UGet_Straf_Location_BTT()
{
	bNotifyTick = true;
	NodeName = TEXT("Get Straf Location");
}

EBTNodeResult::Type UGet_Straf_Location_BTT::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
    FNavLocation NewLocationSearch;

	auto const AiControl = Cast<ACombat_AI_Con>(owner_comp.GetAIOwner());
    auto const Vehicle = AiControl->GetPawn();

    UNavigationSystemV1* const WorldNavSys = UNavigationSystemV1::GetCurrent(GetWorld());
    if (!WorldNavSys) { return EBTNodeResult::Failed; }

    AActor* const TargetActor = Cast<AActor>(AiControl->GetBlackboard()->GetValueAsObject(TargetKey.SelectedKeyName));
    if(!TargetActor) { return EBTNodeResult::Failed; }
    FVector const TargetPos = TargetActor->GetActorLocation();

    if (WorldNavSys->GetRandomPointInNavigableRadius(TargetPos, Radius, NewLocationSearch, nullptr))
    {
        AiControl->GetBlackboard()->SetValueAsVector(GetSelectedBlackboardKey(), NewLocationSearch.Location);
    }

    FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);

    return EBTNodeResult::Succeeded;
}
