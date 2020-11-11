// Alex Chatt Terraform_Conquest 2020

#include "../../Public/Vehicle/Vehicle.h"
#include "../../Public/Components/Health_Component.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AVehicle::AVehicle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	SetRootComponent(MyMesh);

	MyHealth = CreateDefaultSubobject<UHealth_Component>(TEXT("MyHealthComp"));
	MyHealth->bEditableWhenInherited = true;

	FPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyFPSCam"));
	FPSCamera->bUsePawnControlRotation = false;
	FPSCamera->SetupAttachment(MyMesh);

	TPSCameraSpring = CreateDefaultSubobject<USpringArmComponent>(TEXT("TPSCamSpring"));
	TPSCameraSpring->bUsePawnControlRotation = false;
	TPSCameraSpring->SetupAttachment(MyMesh);

	TPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyTPSCam"));
	TPSCamera->bUsePawnControlRotation = false;
	TPSCamera->SetupAttachment(TPSCameraSpring);
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

void AVehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Change_Camera"), EInputEvent::IE_Released, this, &AVehicle::CameraChange);

}

void AVehicle::CameraChange()
{
	BIs1stPersonCamera = !BIs1stPersonCamera;
	FPSCamera->SetActive(BIs1stPersonCamera);
	TPSCamera->SetActive(!BIs1stPersonCamera);
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
