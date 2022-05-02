// Alex Chatt Terraform_Conquest 2020

#include "Controller/Combat_AI_Con.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"

ACombat_AI_Con::ACombat_AI_Con()
{
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
	BlackBoardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
}

void ACombat_AI_Con::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(BehaviorTree);
	BehaviorTreeComp->StartTree(*BehaviorTree);
}


void ACombat_AI_Con::SetupPerceptionSystem()
{
	AISightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AI Sight"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception Comp")));
}

void ACombat_AI_Con::SetPawn(APawn* const InPawn)
{
	Super::SetPawn(InPawn);

}

void ACombat_AI_Con::OnPossess(APawn* const InPawn)
{
	Super::OnPossess(InPawn);
	if (BlackBoardComp)
	{
		BlackBoardComp->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	}
}


UBlackboardComponent* ACombat_AI_Con::GetBlackboard() const
{
	return BlackBoardComp;
}