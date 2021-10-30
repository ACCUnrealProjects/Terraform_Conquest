// Alex Chatt Terraform_Conquest 2020

#include "../../Public/Controller/Main_Player_Controller.h"
#include "../../Public/Components/Health_Component.h"
#include "../../Public/Map/MapControllerV2.h"
#include "Kismet/GameplayStatics.h"

AMain_Player_Controller::AMain_Player_Controller()
{
	PrimaryActorTick.bCanEverTick = true;
	SetTeamID(FGenericTeamId(1));
}

void AMain_Player_Controller::BeginPlay()
{
	Super::BeginPlay();

	AActor* MapControllerActor = UGameplayStatics::GetActorOfClass(GetWorld(), AMapControllerV2::StaticClass());
	if (ensure(MapControllerActor))
	{
		MapController = Cast<AMapControllerV2>(MapControllerActor);
	}
}

void AMain_Player_Controller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMain_Player_Controller::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		UHealth_Component* PawnHealthComp = InPawn->FindComponentByClass<UHealth_Component>();
		if (PawnHealthComp)
		{
			PawnHealthComp->IHaveDied.AddUniqueDynamic(this, &AMain_Player_Controller::MyPawnHasDied);
		}
	}
}

void AMain_Player_Controller::SetupInputComponent()
{
	Super::SetupInputComponent();
	check(InputComponent);
	EnableInput(this);
}

void AMain_Player_Controller::SetTeamID(FGenericTeamId TeamID)
{
	TeamId = TeamID;
}

FGenericTeamId AMain_Player_Controller::GetTeamId() const
{
	return TeamId;
}

void AMain_Player_Controller::MyPawnHasDied()
{
	StartSpectatingOnly();
	//UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), true);
}
