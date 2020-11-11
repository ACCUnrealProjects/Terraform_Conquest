// Alex Chatt Terraform_Conquest 2020

#include "../../Public/Controller/Main_Player_Controller.h"
#include "../../Public/Components/Health_Component.h"
#include "../../Public/Map/MapController.h"
#include "../../Public/Map/BuildController.h"
#include "Kismet/GameplayStatics.h"

AMain_Player_Controller::AMain_Player_Controller()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMain_Player_Controller::BeginPlay()
{
	Super::BeginPlay();
	CurrentMode = ControlMode::FreeDrive;

	AActor* BuildControllerActor = UGameplayStatics::GetActorOfClass(GetWorld(), ABuildController::StaticClass());
	if (ensure(BuildControllerActor))
	{
		BuildingController = Cast<ABuildController>(BuildControllerActor);
	}

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
}


void AMain_Player_Controller::ExectutionAction()
{
	switch (CurrentMode)
	{
	case ControlMode::BuildingPlacement:
		BuildingPlacementTest();
		break;

	case ControlMode::UnitSelected:
		break;

	case ControlMode::Selection:
		break;
	}
}

void AMain_Player_Controller::BuildingPlacementTest()
{
	FVector GroundLocation;

	if (MapController != NULL)
	{
		FHitResult LandscapeRay;
		FVector RayStart = GetPawn()->GetActorLocation();
		FVector RayEnd = RayStart + (GetPawn()->GetActorForwardVector() * 100000);
		if (GetWorld()->LineTraceSingleByChannel(LandscapeRay, RayStart, RayEnd, ECollisionChannel::ECC_GameTraceChannel2))
		{
			UE_LOG(LogTemp, Warning, TEXT("Looking at ground location %s"), *LandscapeRay.ImpactPoint.ToString());
			MapController->GetTileImLookingAt(LandscapeRay.ImpactPoint);
		}
	}
}

void AMain_Player_Controller::MyPawnHasDied()
{
	StartSpectatingOnly();
	//UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), true);
}