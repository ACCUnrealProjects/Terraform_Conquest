// Alex Chatt Terraform_Conquest 2020

#include "Building/Turret.h"
#include "Components/Turret_Aiming_Component.h"
#include "Components/Health_Component.h"
#include "MeshComponents/Barrel_Mesh.h"
#include "MeshComponents/Turret_Mesh.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "Net/UnrealNetwork.h"
#include "Weapons/Weapon.h"

ATurret::ATurret()
{
	MyHealthComp->SetUp(200, 100);

	MyAimingComp = CreateDefaultSubobject<UTurret_Aiming_Component>(TEXT("MyAimingComponent"));
	MyAimingComp->bEditableWhenInherited = true;
	MyAimingComp->SetIsReplicated(true);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BaseAsset(TEXT("StaticMesh'/Game/Meshes/Turret/mortar_body.mortar_body'"));
	BuildingMesh->SetStaticMesh(BaseAsset.Object);

	MyTurret = CreateDefaultSubobject<UTurret_Mesh>(TEXT("MyTurret"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TurretAsset(TEXT("StaticMesh'/Game/Meshes/Turret/mortar_dome.mortar_dome'"));
	MyTurret->SetStaticMesh(TurretAsset.Object);
	MyTurret->SetupAttachment(BuildingMesh, "Turret");

	MyBarrel = CreateDefaultSubobject<UBarrel_Mesh>(TEXT("MyBarrel"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BarrelAsset(TEXT("StaticMesh'/Game/Meshes/Turret/mortar_barrel.mortar_barrel'"));
	MyBarrel->SetStaticMesh(BarrelAsset.Object);
	MyBarrel->SetupAttachment(BuildingMesh, "Barrel");

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	SetUpMyStimulis();

	Tags.Add("Turret");
}

void ATurret::SetUpMyStimulis()
{
	Stimulus = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("MyAIStim"));
	Stimulus->RegisterForSense(TSubclassOf<UAISense_Sight>());
	Stimulus->RegisterWithPerceptionSystem();
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = GetOwner();
		SpawnParams.Instigator = Cast<APawn>(SpawnParams.Owner);

		for (int32 i = 0; i < TurretGuns; i++)
		{
			AWeapon* NewGun = GetWorld()->SpawnActor<AWeapon>(WeaponBlueprint, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(), SpawnParams);
			NewGun->AttachToComponent(MyBarrel, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), "FireLocation");
			NewGun->ChangeActiveState(true);
			TurretWeapons.Add(NewGun);
		}
		MyAimingComp->SetUp(MyTurret, MyBarrel);
	}
}


void ATurret::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Replicate everywhere
	DOREPLIFETIME(ATurret, TurretWeapons);
	DOREPLIFETIME(ATurret, Range);
	DOREPLIFETIME(ATurret, bActivated);

	//Replicate to owner client and server only

	//Replicate to none owner client and server only
}


void ATurret::Fire(AActor* Target)
{
	if (!MyAimingComp->CloseToHittingTarget(Target->GetActorLocation())) { return; }

	for (auto Gun : TurretWeapons)
	{
		Gun->AttemptToFire();
	}
}

void ATurret::AimAt(AActor* Target)
{
	MyAimingComp->AimToTarget(Target->GetActorLocation());
}

bool ATurret::AmILookingAtTargetDir(FVector Direction)
{
	FVector LocationInDirection = (Direction * 100) + MyTurret->GetComponentLocation();

	MyAimingComp->AimToTarget(LocationInDirection);

	if (MyAimingComp->CloseToHittingTarget(LocationInDirection))
	{
		return true;
	}

	return false;
}

void ATurret::SetActiveState(bool bAmIActive)
{
	ServerSetActiveState(bAmIActive);
}

bool ATurret::ServerSetActiveState_Validate(bool bAmIActive)
{
	return true;
}

void ATurret::ServerSetActiveState_Implementation(bool bAmIActive)
{
	bActivated = bAmIActive;
	if (bActivated)
	{
		MyHealthComp->SetUp(200, 100);
	}
}

bool ATurret::GetActiveState()
{
	return bActivated;
}

void ATurret::Death()
{
	//make me idle
	SetActiveState(false);
}