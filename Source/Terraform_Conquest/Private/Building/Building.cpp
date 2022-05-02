// Alex Chatt Terraform_Conquest 2020
// https://forums.unrealengine.com/development-discussion/c-gameplay-programming/1569711-how-do-i-use-the-ai-perception-teams

#include "Building/Building.h"
#include "Map/MapTile.h"
#include "Net/UnrealNetwork.h"
#include "Components/Health_Component.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ABuilding::ABuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	bNetLoadOnClient = true;
	SetReplicateMovement(true);

	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	SetRootComponent(BuildingMesh);
	BuildingMesh->bEditableWhenInherited = true;

	BuildOverlapSpace = CreateDefaultSubobject<UBoxComponent>(TEXT("Bounding Box"));
	BuildOverlapSpace->SetupAttachment(BuildingMesh);
	BuildOverlapSpace->bEditableWhenInherited = true;

	MyHealthComp = CreateDefaultSubobject<UHealth_Component>(TEXT("MyHealthComp"));
	MyHealthComp->bEditableWhenInherited = true;
	MyHealthComp->SetIsReplicated(true);

	Tags.Add("Building");
}

// Called when the game starts or when spawned
void ABuilding::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		MyHealthComp->IHaveDied.AddUniqueDynamic(this, &ABuilding::Death);
	}
}

void ABuilding::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Replicate everywhere
	DOREPLIFETIME(ABuilding, TeamId);

	//Replicate to owner client and server only

	//Replicate to none owner client and server only
}

// Called every frame
void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABuilding::SetTilesImOn(TArray<AMapTile*> BuiltTiles)
{
	TilesImOn = BuiltTiles;
}

void ABuilding::SetTeamID(ETeam NewTeamID)
{
	ServerSetTeamID(NewTeamID);
}

bool ABuilding::ServerSetTeamID_Validate(ETeam NewTeamID)
{
	return true;
}

void ABuilding::ServerSetTeamID_Implementation(ETeam NewTeamID)
{
	Tags.Remove(FName(GetTeamName(TeamId)));
	TeamId = NewTeamID;
	Tags.Add(FName(GetTeamName(TeamId)));
}

ETeam ABuilding::GetTeamId() const
{
	return TeamId;
}

float ABuilding::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (MyHealthComp && HasAuthority())
	{
		return MyHealthComp->TakeDamage(DamageAmount);
	}
	else
	{
		return DamageAmount;
	}
}

void ABuilding::Death()
{
	DestroyCleanUp();
}

void ABuilding::DestroyCleanUp()
{
	for (int32 i = 0; i < TilesImOn.Num(); i++)
	{
		TilesImOn[i]->SetAvailablity(true);
	}
}