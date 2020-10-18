// Alex Chatt Terraform_Conquest 2020

#include "../../Public/Projectile/Mine.h"
#include "../../Public/Components/Health_Component.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMine::AMine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerSphere = CreateDefaultSubobject<USphereComponent>(FName(TEXT("Collision Mesh")));
	SetRootComponent(TriggerSphere);

	MineMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Mesh")));
	MineMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ActivateEffect = CreateDefaultSubobject<UParticleSystemComponent>(FName(TEXT("Impact Blast")));
	ActivateEffect->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ActivateEffect->bAutoActivate = false;

	MyHealthComp = CreateDefaultSubobject<UHealth_Component>(FName(TEXT("Health Comp")));
	MyHealthComp->bEditableWhenInherited = true;
}


// Called when the game starts or when spawned
void AMine::BeginPlay()
{
	Super::BeginPlay();

	TriggerSphere->SetSphereRadius(TriggerRadius);
	TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &AMine::MineOverlapped);
	TriggerSphere->Deactivate();

	MyHealthComp->IHaveDied.AddUniqueDynamic(this, &AMine::Death);

	FTimerHandle ActivateTimer;
	GetWorld()->GetTimerManager().SetTimer(ActivateTimer, this, &AMine::ActivateMine, ActivationTime, false);
}

// Called every frame
void AMine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMine::ActivateMine()
{
	TriggerSphere->Activate();
}

void AMine::Trigger()
{
	Death();
}

void AMine::MineOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Trigger();
}

void AMine::Death()
{
	FTimerHandle DeathTimer;
	GetWorld()->GetTimerManager().SetTimer(DeathTimer, this, &AMine::DestoryMe, DestroyTime, false);
}

void AMine::DestoryMe()
{
	Destroy();
}