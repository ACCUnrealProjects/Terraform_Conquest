// Alex Chatt Terraform_Conquest 2020

#include "../../Public/Controller/Main_Player_Controller.h"
#include "../../Public/Components/Health_Component.h"
#include "../../Public/Map/MapController.h"
#include "../../Public/Map/BuildController.h"
#include "Kismet/GameplayStatics.h"

AMain_Player_Controller::AMain_Player_Controller()
{
	PrimaryActorTick.bCanEverTick = true;
	SetTeamID(FGenericTeamId(1));
}

void AMain_Player_Controller::BeginPlay()
{
	Super::BeginPlay();
	CurrentMode = ControlMode::FreeDrive;

	BuildingController = GetWorld()->SpawnActor<ABuildController>(ABuildController::StaticClass());
	BuildingController->SetTeamID(TeamId);

	AActor* MapControllerActor = UGameplayStatics::GetActorOfClass(GetWorld(), AMapController::StaticClass());
	if (ensure(MapControllerActor))
	{
		MapController = Cast<AMapController>(MapControllerActor);
	}
}

void AMain_Player_Controller::Tick(float DeltaTime)
{
	switch (CurrentMode)
	{
	case ControlMode::BuildingPlacement:
	{
		FHitResult LandscapeRay;
		FVector RayStart = GetPawn()->GetActorLocation();
		FVector RayEnd = RayStart + (GetPawn()->GetActorForwardVector() * 100000);
		if (GetWorld()->LineTraceSingleByChannel(LandscapeRay, RayStart, RayEnd, ECollisionChannel::ECC_GameTraceChannel2))
		{
			BuildingController->SetBluePrintLocation(LandscapeRay.ImpactPoint, MapController->GetTileImLookingAt(LandscapeRay.ImpactPoint));
		}
	}
	break;
	case ControlMode::UnitSelected:
	{

	}
	break;
	case ControlMode::Selection:
	{

	}
	break;
	}
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

	InputComponent->BindAction(TEXT("ExecuteOrder"), EInputEvent::IE_Released, this, &AMain_Player_Controller::ExectutionAction).bConsumeInput = false;
	InputComponent->BindAction(TEXT("Escape"), EInputEvent::IE_Released, this, &AMain_Player_Controller::CancelAction);
}


void AMain_Player_Controller::ExectutionAction()
{
	switch (CurrentMode)
	{
	case ControlMode::BuildingPlacement:
	{
		BuildingPlacement();
		break;
	}
	case ControlMode::UnitSelected:
	{
		break;
	}
	case ControlMode::Selection:
	{
		break;
	}
	}
}

void AMain_Player_Controller::CancelAction()
{
	switch (CurrentMode)
	{
	case ControlMode::BuildingPlacement:
	{
		BuildingController->CancelBuild();
		CurrentMode = ControlMode::FreeDrive;
		break;
	}
	case ControlMode::UnitSelected:
	{
		break;
	}
	case ControlMode::Selection:
	{
		break;
	}
	}
}

void AMain_Player_Controller::BuildingPlacement()
{
	FString BuildMessage;
	if (BuildingController->AttemptedToBuild(BuildMessage))
	{
		CurrentMode = ControlMode::FreeDrive;
	}
	else
	{

	}
}

void AMain_Player_Controller::StartPowerSpawn()
{
	if (CurrentMode != ControlMode::BuildingPlacement)
	{
		//CurrentMode = ControlMode::BuildingPlacement;
		//BuildingController->CreateBuildingBlueprint(BuildingControllerSubClass);
	}
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
