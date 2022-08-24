// Alex Chatt Terraform_Conquest 2020

#include "Components/MiniMapIcon_Component.h"
#include "Controller/Main_Player_Controller.h"

// Sets default values for this component's properties
UMiniMapIcon_Component::UMiniMapIcon_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}

// Called when the game starts
void UMiniMapIcon_Component::BeginPlay()
{
	Super::BeginPlay();

	// Horrible to use a timer, new solution to problem needed where 
	// owner is not yet the player controller at creation
	if (GetWorld()->GetFirstPlayerController())
	{
		FTimerHandle MiniMapIconSetUp;
		GetWorld()->GetTimerManager().SetTimer(MiniMapIconSetUp, this, &UMiniMapIcon_Component::CreateIcon, 0.5f, false);
	}
}

void UMiniMapIcon_Component::SetUp(bool bAmIStatic, UTexture2D* Texture2d)
{
	bIsStatic = bAmIStatic;
	IconImage = Texture2d;
}

void UMiniMapIcon_Component::CreateIcon()
{
	AMain_Player_Controller* MPCon = nullptr;

	// Dont add mark for my own actor
	auto LocalPlayerActor = GetWorld()->GetFirstPlayerController();
	auto OwnerActor = GetOwner()->GetOwner();
	if (LocalPlayerActor == OwnerActor)
	{
		return;
	}

	if (LocalPlayerActor)
	{
		MPCon = Cast<AMain_Player_Controller>(LocalPlayerActor);
		if (MPCon)
		{
			MPCon->NewActorForMap(bIsStatic, GetOwner());
		}
	}
}



