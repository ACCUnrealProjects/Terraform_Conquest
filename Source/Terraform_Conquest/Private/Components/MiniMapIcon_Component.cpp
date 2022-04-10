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

	AMain_Player_Controller* MPCon = nullptr;

	// Dont add mark for my own actor
	if (Cast<AActor>(GetWorld()->GetFirstPlayerController()->GetPawn()) == GetOwner())
	{
		return;
	}

	if (GetWorld()->GetFirstPlayerController())
	{
		MPCon = Cast<AMain_Player_Controller>(GetWorld()->GetFirstPlayerController());
		if (MPCon)
		{
			MPCon->NewActorForMap(bIsStatic, GetOwner());
		}
	}

}

void UMiniMapIcon_Component::SetUp(bool bAmIStatic, UTexture2D* Texture2d)
{
	bIsStatic = bAmIStatic;
	IconImage = Texture2d;
}



