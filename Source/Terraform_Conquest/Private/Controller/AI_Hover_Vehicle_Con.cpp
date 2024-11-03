// Alex Chatt Terraform_Conquest 2020

#include "Controller/AI_Hover_Vehicle_Con.h"
#include "Components/Health_Component.h"
#include "Vehicle/HoverVehicles/Hover_Vehicles.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"

AAI_Hover_Vehicle_Con::AAI_Hover_Vehicle_Con()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj(TEXT("BehaviorTree'/Game/AI/Hover_Vehicle_BT.Hover_Vehicle_BT'"));
	if (obj.Succeeded())
	{
		BehaviorTree = obj.Object;
	}
	SetupPerceptionSystem();
}

void AAI_Hover_Vehicle_Con::OnTargetDetected(AActor* actor, FAIStimulus const stimulus)
{
	if (actor && actor == Cast<AActor>(GetWorld()->GetFirstPlayerController()->GetPawn()))
	{
		GetBlackboard()->SetValueAsBool(TEXT("bCanSeeTarget"), stimulus.WasSuccessfullySensed());
	}
}

void AAI_Hover_Vehicle_Con::SetupPerceptionSystem()
{
	Super::SetupPerceptionSystem();

	AISightConfig->SightRadius = 3000.0f;
	AISightConfig->LoseSightRadius = AISightConfig->SightRadius * 4.0f;
	AISightConfig->PeripheralVisionAngleDegrees = 360.0f;
	AISightConfig->SetMaxAge(5.0f);
	AISightConfig->AutoSuccessRangeFromLastSeenLocation = 1000.0f;
	AISightConfig->DetectionByAffiliation.bDetectEnemies = true;
	AISightConfig->DetectionByAffiliation.bDetectFriendlies = false;
	AISightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*AISightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AAI_Hover_Vehicle_Con::OnTargetDetected);
	GetPerceptionComponent()->ConfigureSense(*AISightConfig);
}

void AAI_Hover_Vehicle_Con::BeginPlay()
{
	Super::BeginPlay();
}

void AAI_Hover_Vehicle_Con::OnPossess(APawn* const InPawn)
{
	Super::OnPossess(InPawn);
}

void AAI_Hover_Vehicle_Con::SetPawn(APawn* const InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		UHealth_Component* PawnsHealthCon = InPawn->FindComponentByClass<UHealth_Component>();
		if (!ensure(PawnsHealthCon)) { return; }
		PawnsHealthCon->IHaveDied.AddUniqueDynamic(this, &AAI_Hover_Vehicle_Con::PawnHasDiedListener);
	}
}

void AAI_Hover_Vehicle_Con::PawnHasDiedListener()
{
	if (!GetPawn()) { return; }
}

