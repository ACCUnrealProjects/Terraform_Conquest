// Alex Chatt Terraform_Conquest 2020

#include "../../Public/Vehicle/Vehicle.h"
#include "../../Public/Components/Health_Component.h"
#include "Camera/CameraComponent.h"

// Sets default values
AVehicle::AVehicle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	SetRootComponent(MyMesh);

	MyHealth = CreateDefaultSubobject<UHealth_Component>(TEXT("MyHealthComp"));
	MyHealth->bEditableWhenInherited = true;

	FPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyFPSCam"));
	FPSCamera->bUsePawnControlRotation = false;
	FPSCamera->SetupAttachment(MyMesh);

	TPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyTPSCam"));
	TPSCamera->bUsePawnControlRotation = false;
	TPSCamera->SetupAttachment(MyMesh);
	TPSCamera->Deactivate();

}


// Called when the game starts or when spawned
void AVehicle::BeginPlay()
{
	Super::BeginPlay();
	MyMesh->SetCenterOfMass(FVector(0, 0, -100));

	MyHealth->IHaveDied.AddUniqueDynamic(this, &AVehicle::Death);
	MyHealth->IHaveBeenHit.AddUniqueDynamic(this, &AVehicle::imHit);
}

// Called every frame
void AVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVehicle::Death()
{
	FTimerHandle DeathTimer;
	GetWorld()->GetTimerManager().SetTimer(DeathTimer, this, &AVehicle::DestoryMe, DestroyTime, false);
}

void AVehicle::imHit()
{

}

void AVehicle::DestoryMe()
{
	Destroy();
}
