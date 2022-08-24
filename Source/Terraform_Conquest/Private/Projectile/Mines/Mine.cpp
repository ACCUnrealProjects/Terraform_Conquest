// Alex Chatt Terraform_Conquest 2020

#include "Projectile/Mines/Mine.h"
#include "Components/Health_Component.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMine::AMine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	bNetLoadOnClient = true;
	SetReplicateMovement(true);

	TriggerSphere = CreateDefaultSubobject<USphereComponent>(FName(TEXT("Collision Mesh")));
	SetRootComponent(TriggerSphere);

	MineMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Mesh")));
	MineMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ActivateEffect = CreateDefaultSubobject<UParticleSystemComponent>(FName(TEXT("Impact Blast")));
	ActivateEffect->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ActivateEffect->bAutoActivate = false;

	MyHealthComp = CreateDefaultSubobject<UHealth_Component>(FName(TEXT("Health Comp")));
	MyHealthComp->bEditableWhenInherited = true;
	MyHealthComp->SetIsReplicated(true);
	MyHealthComp->SetUp(1, 0);

	Tags.Add("Mine");
}


// Called when the game starts or when spawned
void AMine::BeginPlay()
{
	Super::BeginPlay();

	TriggerSphere->SetSphereRadius(TriggerRadius);
	TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &AMine::MineOverlapped);
	TriggerSphere->Deactivate();

	if (HasAuthority())
	{
		FTimerHandle ActivateTimer;
		GetWorld()->GetTimerManager().SetTimer(ActivateTimer, this, &AMine::ActivateMine, ActivationTime, false);

		MyHealthComp->IHaveDied.AddUniqueDynamic(this, &AMine::Death);
	}

}

void AMine::ActivateMine()
{
	TriggerSphere->Activate();
}

float AMine::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (MyHealthComp) { return MyHealthComp->TakeDamage(DamageAmount); }
	else { return DamageAmount; }
}

void AMine::Trigger()
{
	Death();
}

void AMine::MineOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!HasAuthority()) { return; }

	for (auto myTag : Tags)
	{
		for (auto OtherTag : OtherActor->Tags)
		{
			// Check to make sure we are not blowing up on a Friendly
			if (myTag == OtherTag &&
				myTag.ToString().Find("ETeam"))
			{
				return;
			}
		}
	}
	Trigger();
}

void AMine::Death()
{
	if (HasAuthority())
	{
		FTimerHandle DeathTimer;
		GetWorld()->GetTimerManager().SetTimer(DeathTimer, this, &AMine::DestoryMe, DestroyTime, false);
	}
}

void AMine::DestoryMe()
{
	Destroy();
}