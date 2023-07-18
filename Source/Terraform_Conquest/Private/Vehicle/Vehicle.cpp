// Alex Chatt Terraform_Conquest 2020

#include "Vehicle/Vehicle.h"
#include "Components/Health_Component.h"
#include "Components/Weapon_Controller_Component.h"
#include "Components/MiniMapIcon_Component.h"
#include "Components/RectLightComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Blueprint/UserWidget.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/SpringArmComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "Camera/CameraComponent.h"

// Sets default values
AVehicle::AVehicle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	bNetLoadOnClient = true;
	SetReplicateMovement(false);

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	SetRootComponent(MyMesh);

	MyHealth = CreateDefaultSubobject<UHealth_Component>(TEXT("MyHealthComp"));
	MyHealth->bEditableWhenInherited = true;
	MyHealth->SetIsReplicated(true);

	FPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyFPSCam"));
	FPSCamera->bUsePawnControlRotation = false;
	FPSCamera->SetupAttachment(GetRootComponent());

	TPSCameraSpring = CreateDefaultSubobject<USpringArmComponent>(TEXT("TPSCamSpring"));
	TPSCameraSpring->bUsePawnControlRotation = false;
	TPSCameraSpring->bEnableCameraLag = true;
	TPSCameraSpring->bEnableCameraRotationLag = true;
	TPSCameraSpring->SetupAttachment(GetRootComponent());

	TPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyTPSCam"));
	TPSCamera->bUsePawnControlRotation = false;
	TPSCamera->SetupAttachment(TPSCameraSpring);

	VehicleWeaponControllerComp = CreateDefaultSubobject<UWeapon_Controller_Component>(TEXT("VehicleWeaponSystem"));
	VehicleWeaponControllerComp->bEditableWhenInherited = true;
	VehicleWeaponControllerComp->SetIsReplicated(true);

	MiniMapIconComp = CreateDefaultSubobject<UMiniMapIcon_Component>(TEXT("MyMiniMapIcon"));
	MiniMapIconComp->bEditableWhenInherited = true;
	MiniMapIconComp->SetIsReplicated(true);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	SetUpMyStimulis();

	Tags.Add("Vehicle");
}

void AVehicle::SetUpMyStimulis()
{
	Stimulus = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("MyAIStim"));
	Stimulus->RegisterForSense(TSubclassOf<UAISense_Sight>());
	Stimulus->RegisterWithPerceptionSystem();
}

// Called when the game starts or when spawned
void AVehicle::BeginPlay()
{
	Super::BeginPlay();

	MyMesh->SetCenterOfMass(FVector(0, 0, -100));
	if (HasAuthority())
	{
		MyHealth->IHaveDied.AddUniqueDynamic(this, &AVehicle::Death);
		GetComponents<URectLightComponent>(Lights);
	}
}

void AVehicle::SetUpLights()
{
	TArray<FName> LightNames = { FName(TEXT("Light_1")), FName(TEXT("Light_2")) };

	if (!MyMesh) { return; }

	for (auto LightName : LightNames)
	{
		if (MyMesh->DoesSocketExist(LightName))
		{
			URectLightComponent* NewLight = CreateDefaultSubobject<URectLightComponent>(LightName);
			NewLight->bEditableWhenInherited = true;
			NewLight->SetupAttachment(MyMesh, LightName);
			NewLight->SetVisibility(bAreLightsOn);
			NewLight->SetIsReplicated(true);
		}
	}
}

void AVehicle::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Replicate everywhere
	DOREPLIFETIME(AVehicle, MyPosition);
	DOREPLIFETIME(AVehicle, MyRotation);
	DOREPLIFETIME(AVehicle, Lights);

	//Replicate to owner client and server only
	//DOREPLIFETIME_CONDITION(AVehicle, WantToFire, COND_OwnerOnly);

	//Replicate to none owner client and server only
}

// Called every frame
void AVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (WantToFire && IsLocallyControlled())
	{
		VehicleWeaponControllerComp->FireCurrent();
	}

	UpdateTransform();
}

void AVehicle::UpdateTransform()
{
	if (IsLocallyControlled())
	{
		if (HasAuthority())
		{
			MyPosition = GetActorLocation();
			MyRotation = GetActorRotation();
		}
		else
		{
			ServerSetTransform(GetActorLocation(), GetActorRotation());
		}
	}
	else
	{
		FVector NewPos = FMath::VInterpTo(GetActorLocation(), MyPosition, GetWorld()->GetDeltaSeconds(), 50.0f);
		FRotator NewRot = FMath::RInterpTo(GetActorRotation(), MyRotation, GetWorld()->GetDeltaSeconds(), 50.0f);
		SetActorLocation(NewPos);
		SetActorRotation(NewRot);
	}
}

bool AVehicle::ServerSetTransform_Validate(FVector NewPosition, FRotator NewRotation)
{
	return true;
}

void AVehicle::ServerSetTransform_Implementation(FVector NewPosition, FRotator NewRotation)
{
	MyPosition = NewPosition;
	MyRotation = NewRotation;
}

void AVehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	//Change Camera
	PlayerInputComponent->BindAction(TEXT("Change_Camera"), EInputEvent::IE_Released, this, &AVehicle::CameraChange);
	//Weapon System
	PlayerInputComponent->BindAction(TEXT("LeftClickAction"), EInputEvent::IE_Pressed, this, &AVehicle::Fire);
	PlayerInputComponent->BindAction(TEXT("LeftClickAction"), EInputEvent::IE_Released, this, &AVehicle::StopFiring);
	PlayerInputComponent->BindAction(TEXT("RightClickAction"), EInputEvent::IE_Pressed, this, &AVehicle::ChangeWeapon);
	//Lights
	PlayerInputComponent->BindAction(TEXT("Lights"), EInputEvent::IE_Pressed, this, &AVehicle::ToggleLights);
}

void AVehicle::CameraChange()
{
	BIs1stPersonCamera = !BIs1stPersonCamera;
	FPSCamera->SetActive(BIs1stPersonCamera);
	TPSCamera->SetActive(!BIs1stPersonCamera);
	ServerCameraChange(BIs1stPersonCamera);
}

bool AVehicle::ServerCameraChange_Validate(bool bIsFPSCam)
{
	return true;
}

void AVehicle::ServerCameraChange_Implementation(bool bIsFPSCam)
{
	MultiCameraChange(bIsFPSCam);
}

void AVehicle::MultiCameraChange_Implementation(bool bIsFPSCam)
{
	FPSCamera->SetActive(BIs1stPersonCamera);
	TPSCamera->SetActive(!BIs1stPersonCamera);
}

void AVehicle::Fire()
{
	WantToFire = true;
}

void AVehicle::StopFiring()
{
	WantToFire = false;
}

void AVehicle::ChangeWeapon()
{
	VehicleWeaponControllerComp->SwitchWeapon();
}

void AVehicle::ToggleLights()
{
	bAreLightsOn = !bAreLightsOn;
	ServerToggleLights(bAreLightsOn);
}

bool AVehicle::ServerToggleLights_Validate(bool bLightState)
{
	return true;
}

void AVehicle::ServerToggleLights_Implementation(bool bLightState)
{
	MultiToggleLights(bLightState);
}

void AVehicle::MultiToggleLights_Implementation(bool bLightState)
{
	auto test = GetNetMode();

	for (auto Light : Lights)
	{
		if (Light)
		{
			Light->SetVisibility(bLightState);
		}
	}
}

float AVehicle::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (MyHealth && HasAuthority())
	{ 
		return MyHealth->TakeDamage(DamageAmount); 
	}
	else 
	{ 
		return DamageAmount; 
	}
}

void AVehicle::Death()
{
	FTimerHandle DeathTimer;
	MyMesh->SetCenterOfMass(FVector(0, 0, 0));
	GetWorld()->GetTimerManager().SetTimer(DeathTimer, this, &AVehicle::DestoryMe, DestroyTime, false);
}

void AVehicle::DestoryMe()
{
	Destroy();
}
