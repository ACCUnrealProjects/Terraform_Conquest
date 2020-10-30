// Alex Chatt Terraform_Conquest 2020

#include "../../Public/Controller/Main_Player_Controller.h"
#include "../../Public/Components/Health_Component.h"
#include "../../Public/Map/MapController.h"
#include "Kismet/GameplayStatics.h"

AMain_Player_Controller::AMain_Player_Controller()
{

}

void AMain_Player_Controller::BeginPlay()
{
	Super::BeginPlay();
	CurrentMode = ControlMode::FreeDrive;

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

	InputComponent->BindAction("LeftClickAction", EInputEvent::IE_Pressed, this, &AMain_Player_Controller::BuildingPlacementTest);
}

void AMain_Player_Controller::BuildingPlacementTest()
{
	FVector GroundLocation;

	TArray<AActor*> MapController;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMapController::StaticClass(), MapController);
	if (MapController[0] != NULL)
	{
		FHitResult LandscapeRay;
		FVector RayStart = GetPawn()->GetActorLocation();
		FVector RayEnd = RayStart + (GetPawn()->GetActorForwardVector() * 100000);
		if (GetWorld()->LineTraceSingleByChannel(LandscapeRay, RayStart, RayEnd, ECollisionChannel::ECC_GameTraceChannel2))
		{
			UE_LOG(LogTemp, Warning, TEXT("Looking at ground location %s"), *LandscapeRay.ImpactPoint.ToString());
			Cast<AMapController>(MapController[0])->GetTileImLookingAt(LandscapeRay.ImpactPoint);
		}
	}
}

void AMain_Player_Controller::MyPawnHasDied()
{
	StartSpectatingOnly();
	//UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), true);
}