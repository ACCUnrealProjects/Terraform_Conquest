// Alex Chatt Terraform_Conquest 2020

#include "AI/Vehicle/GetLocations/Get_Random_Postion_BTT.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "NavigationSystem.h"

#include "Controller/Combat_AI_Con.h"
#include "Vehicle/Vehicle.h"

UGet_Random_Postion_BTT::UGet_Random_Postion_BTT()
{
    NodeName = TEXT("Find Random Location");
}

EBTNodeResult::Type UGet_Random_Postion_BTT::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
    auto const AiControl = Cast<ACombat_AI_Con>(owner_comp.GetAIOwner());
    auto const Vehicle = AiControl->GetPawn();

    FVector const GetCurrentPos = Vehicle->GetActorLocation();
    FNavLocation NewLocationSearch;

    UNavigationSystemV1* const WorldNavSys = UNavigationSystemV1::GetCurrent(GetWorld());
    if (!WorldNavSys) { return EBTNodeResult::Failed; }


    if (WorldNavSys->GetRandomPointInNavigableRadius(GetCurrentPos, Radius, NewLocationSearch, nullptr))
    {
        AiControl->GetBlackboard()->SetValueAsVector(GetSelectedBlackboardKey(), NewLocationSearch.Location);
    }

    FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);

    return EBTNodeResult::Succeeded;
}