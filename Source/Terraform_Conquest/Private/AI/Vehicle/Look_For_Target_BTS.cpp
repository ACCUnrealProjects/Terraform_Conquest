// Alex Chatt Terraform_Conquest 2020

#include "AI/Vehicle/Look_For_Target_BTS.h"
#include "Controller/Combat_AI_Con.h"
#include "BehaviorTree/BlackboardComponent.h"

ULook_For_Target_BTS::ULook_For_Target_BTS()
{
	bNotifyTick = true;
	NodeName = TEXT("Look For Traget");
}

void ULook_For_Target_BTS::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACombat_AI_Con* const MyAI = Cast<ACombat_AI_Con>(OwnerComp.GetAIOwner());
	if (!MyAI) { return; }

	auto const PlayerExists = GetWorld()->GetFirstPlayerController();

	// for now just do this to fire at the player (testing)
	bool SeeTarget = MyAI->GetBlackboard()->GetValueAsBool(CanSeeTargetBool.SelectedKeyName);
	UObject* const TargetActor = MyAI->GetBlackboard()->GetValueAsObject(GetSelectedBlackboardKey());

	if (SeeTarget && !TargetActor)
	{
		MyAI->GetBlackboard()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerExists->GetPawn());
	}
	else if ((!SeeTarget && TargetActor))
	{
		MyAI->GetBlackboard()->SetValueAsObject(GetSelectedBlackboardKey(), nullptr);
	}

}
