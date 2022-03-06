// Alex Chatt Terraform_Conquest 2020

#include "Building/Important/Control_Point.h"
#include "Components/PointLightComponent.h"
#include "Gamestate/Conquest_GameState.h"
#include "Components/WidgetComponent.h"
#include "Net/UnrealNetwork.h"
#include "Vehicle/Vehicle.h"

// Sets default values
AControl_Point::AControl_Point()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;
	bNetLoadOnClient = true;
	SetReplicateMovement(false);

	CapturePointSphere = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Capture Radius")));
	CapturePointSphere->SetGenerateOverlapEvents(true);
	CapturePointSphere->SetCanEverAffectNavigation(false);
	CapturePointSphere->SetIsReplicated(true);
	SetRootComponent(CapturePointSphere);

	CapturePointFlag = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Capture Mesh")));
	CapturePointFlag->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CapturePointFlag->SetIsReplicated(true);

	CapturePointLight = CreateDefaultSubobject<UPointLightComponent>(FName(TEXT("Light")));
	CapturePointLight->AttachToComponent(CapturePointFlag, FAttachmentTransformRules::KeepRelativeTransform);
	CapturePointLight->SetIsReplicated(true);

	CaptureIcon = CreateDefaultSubobject<UWidgetComponent>(FName(TEXT("CaptureIcon")));
	CaptureIcon->AttachToComponent(CapturePointFlag, FAttachmentTransformRules::KeepRelativeTransform);
	CaptureIcon->SetIsReplicated(true);

	Contesters.Add(TTuple<ETeam, int32>(ETeam::Team1, 0));
	Contesters.Add(TTuple<ETeam, int32>(ETeam::Team2, 0));
}

void AControl_Point::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Replicate everywhere
	DOREPLIFETIME(AControl_Point, CapPercentage);
	DOREPLIFETIME(AControl_Point, bBeingCaptured);
	DOREPLIFETIME(AControl_Point, CurrentTeamControl);
	DOREPLIFETIME(AControl_Point, CurrentTeamCapturing);
}

// Called when the game starts or when spawned
void AControl_Point::BeginPlay()
{
	Super::BeginPlay();

	if(HasAuthority())
	{ 
		GetWorldTimerManager().SetTimer(CaptureTickTimer, this, &AControl_Point::CapturingPoint, CaptureTickTime, true);
	}
}

void AControl_Point::CapturedPoint(ETeam TeamThatCaptured)
{
	CurrentTeamControl = TeamThatCaptured;
	if (CurrentTeamControl != ETeam::Neutral)
	{
		GetWorldTimerManager().SetTimer(PointsTickTimer, this, &AControl_Point::ScorePoints, PointsTickTime, true);
	}
	else
	{

	}
}

void AControl_Point::CapturingPoint()
{
	Contesters[ETeam::Team1] = Contesters[ETeam::Team2] = 0;
	TArray<AActor*> ActorsIn;
	CapturePointSphere->GetOverlappingActors(ActorsIn, AVehicle::StaticClass());
	if (!ActorsIn.Num()) { return; }

	for (int16 i = 0; i < ActorsIn.Num(); i++)
	{
		Contesters[Cast<AVehicle>(ActorsIn[0])->GetTeamId()]++;
	}

	ETeam HigherContesters = ETeam::Neutral;

	if (Contesters[ETeam::Team1] > 0 && Contesters[ETeam::Team2] == 0)
	{
		HigherContesters = ETeam::Team1;
	}
	else if (Contesters[ETeam::Team2] > 0 && Contesters[ETeam::Team1] == 0)
	{
		HigherContesters = ETeam::Team2;
	}
	else { return; }

	if (bBeingCaptured)
	{
		CapPercentage = FMath::Clamp(CapPercentage + (Contesters[HigherContesters] * CapturePercentPerPerson),
			0.0f, FullCap);
	}
	else
	{
		CapPercentage = FMath::Clamp(CapPercentage - (Contesters[HigherContesters] * CapturePercentPerPerson),
			0.0f, FullCap);
	}

	if (CapPercentage == FullCap)
	{
		CapturedPoint(HigherContesters);
	}
	else if (CapPercentage == 0)
	{
		if (CurrentTeamControl != ETeam::Neutral)
		{
			GetWorldTimerManager().ClearTimer(PointsTickTimer);
			CapturedPoint(ETeam::Neutral);
		}
		CurrentTeamCapturing = HigherContesters;
		bBeingCaptured = true;
	}
}

void AControl_Point::ScorePoints()
{
	if (!PlayingGameState)
	{
		PlayingGameState = Cast<AConquest_GameState>(GetWorld()->GetGameState());
	}

	if (PlayingGameState)
	{
		PlayingGameState->AddScoreForTeam(CurrentTeamControl, PointsPerTick);
	}
}
