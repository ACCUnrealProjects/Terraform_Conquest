// Alex Chatt Terraform_Conquest 2020

#include "Controller/Turret_Controller.h"
#include "Components/Health_Component.h"
#include "Building/Turret.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"

ATurret_Controller::ATurret_Controller()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj(TEXT("BehaviorTree'/Game/AI/Turret_BT.Turret_BT'"));
	if (obj.Succeeded())
	{
		BehaviorTree = obj.Object;
	}
	SetupPerceptionSystem();
}

void ATurret_Controller::OnTargetDetected(AActor* actor, FAIStimulus const stimulus)
{
	if (actor && actor == Cast<AActor>(GetWorld()->GetFirstPlayerController()->GetPawn()))
	{
		GetBlackboard()->SetValueAsBool(TEXT("CanSeePlayer"), stimulus.WasSuccessfullySensed());
	}
}

void ATurret_Controller::SetupPerceptionSystem()
{
	Super::SetupPerceptionSystem();

	AISightConfig->SightRadius = 5000.0f;
	AISightConfig->LoseSightRadius = AISightConfig->SightRadius * 1.5f;
	AISightConfig->PeripheralVisionAngleDegrees = 360.0f;
	AISightConfig->SetMaxAge(3.0f);
	AISightConfig->AutoSuccessRangeFromLastSeenLocation = 100.0f;
	AISightConfig->DetectionByAffiliation.bDetectEnemies = true;
	AISightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	AISightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*AISightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ATurret_Controller::OnTargetDetected);
	GetPerceptionComponent()->ConfigureSense(*AISightConfig);
}

void ATurret_Controller::BeginPlay()
{
	Super::BeginPlay();
}

void ATurret_Controller::OnPossess(APawn* const InPawn)
{
	Super::OnPossess(InPawn);
}

void ATurret_Controller::SetPawn(APawn* const InPawn)
{
	Super::SetPawn(InPawn);

	/*if (InPawn)
	{
		UHealth_Component* PawnsHealthCon = InPawn->FindComponentByClass<UHealth_Component>();
		if (!ensure(PawnsHealthCon)) { return; }
		PawnsHealthCon->IHaveDied.AddUniqueDynamic(this, &ATurret_Controller::PawnHasDiedListener);
	}*/
}

void ATurret_Controller::PawnHasDiedListener()
{
	if (!GetPawn()) { return; }
	GetWorld()->DestroyActor(GetPawn());
}


