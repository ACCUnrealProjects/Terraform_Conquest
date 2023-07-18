// Alex Chatt Terraform_Conquest 2020

#include "Controller/Main_Player_Controller.h"
#include "Components/Health_Component.h"
#include "Map/MapControllerV2.h"
#include "Net/UnrealNetwork.h"
#include "Vehicle/Vehicle.h"
#include "GameModes/TerraformGameMode.h"
#include "Kismet/GameplayStatics.h"

AMain_Player_Controller::AMain_Player_Controller()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	bNetLoadOnClient = true;
	SetReplicateMovement(false);

	TeamId = ETeam::Neutral;
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

void AMain_Player_Controller::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Replicate everywhere
	DOREPLIFETIME(AMain_Player_Controller, TeamId);

	//Replicate to owner client and server only
	//DOREPLIFETIME_CONDITION(AWeapon, , COND_OwnerOnly);
}

void AMain_Player_Controller::MiniMapIconSetUp()
{
	if (!IsLocalPlayerController()) { return; }

	for (const TPair<AActor*, bool>& NewIcon : NewMiniMapIcon)
	{
		AddActorMarkerToMap(NewIcon.Value, NewIcon.Key);
	}
	NewMiniMapIcon.Empty();
}


void AMain_Player_Controller::NewActorForMap(bool bIsStatic, AActor* OwnerActor)
{
	if (!IsLocalPlayerController()) { return; }

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

void AMain_Player_Controller::ServerSetTeamID_Implementation(ETeam NewTeamID)
{
	TeamId = NewTeamID;
}

void AMain_Player_Controller::ServerCreateNewPawn_Implementation(TSubclassOf <class APawn> PawnType, FTransform SpawnTransform)
{
	if (!GetWorld()) { return; }

	APawn* CurrentPawn = GetPawn();

	ATerraformGameMode* TGameMode = Cast<ATerraformGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!TGameMode) { return; }
	TGameMode->CreatePlayerPawn(PawnType, this, SpawnTransform);

	if (CurrentPawn)
	{
		CurrentPawn->Destroy();
	}
}

void AMain_Player_Controller::MyPawnHasDied()
{
	StartSpectatingOnly();
	//UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), true);
}