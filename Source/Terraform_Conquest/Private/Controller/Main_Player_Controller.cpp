// Alex Chatt Terraform_Conquest 2020

#include "Controller/Main_Player_Controller.h"
#include "Components/Health_Component.h"
#include "Map/MapControllerV2.h"
#include "Vehicle/Vehicle.h"
#include "Kismet/GameplayStatics.h"

AMain_Player_Controller::AMain_Player_Controller()
{
	PrimaryActorTick.bCanEverTick = true;
	SetTeamID(ETeam::Neutral);
}

void AMain_Player_Controller::BeginPlay()
{
	Super::BeginPlay();

	/*AActor* MapControllerActor = UGameplayStatics::GetActorOfClass(GetWorld(), AMapControllerV2::StaticClass());
	if (ensure(MapControllerActor))
	{
		MapController = Cast<AMapControllerV2>(MapControllerActor);
	}*/

	FTimerHandle MiniMapIconSetUp;
	GetWorld()->GetTimerManager().SetTimer(MiniMapIconSetUp, this, &AMain_Player_Controller::MiniMapIconSetUp, 0.5f, false);
}

void AMain_Player_Controller::MiniMapIconSetUp()
{
	for (const TPair<AActor*, bool>& NewIcon : NewMiniMapIcon)
	{
		AddActorMarkerToMap(NewIcon.Value, NewIcon.Key);
	}
	NewMiniMapIcon.Empty();
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

		AVehicle* NewVehicle = Cast<AVehicle>(InPawn);
		if (NewVehicle)
		{
			NewVehicle->SetTeamID(TeamId);
		}
	}

}

void AMain_Player_Controller::NewActorForMap(bool bIsStatic, AActor* OwnerActor)
{
	if (!bMiniMapSetUp)
	{
		NewMiniMapIcon.Add(TPair<AActor*, bool>(OwnerActor, bIsStatic));
		return;
	}

	AddActorMarkerToMap(bIsStatic, OwnerActor);
}

void AMain_Player_Controller::SetupInputComponent()
{
	Super::SetupInputComponent();
	check(InputComponent);
	EnableInput(this);
}

void AMain_Player_Controller::MyPawnHasDied()
{
	StartSpectatingOnly();
	//UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), true);
}
