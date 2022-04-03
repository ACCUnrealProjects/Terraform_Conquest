// Alex Chatt Terraform_Conquest 2020

#include "Components/PointOfInterest_Component.h"
#include "Controller/Main_Player_Controller.h"

// Sets default values for this component's properties
UPointOfInterest_Component::UPointOfInterest_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}

// Called when the game starts
void UPointOfInterest_Component::BeginPlay()
{
	Super::BeginPlay();

	AMain_Player_Controller* MPCon = nullptr;

	if (GetWorld()->GetFirstPlayerController())
	{
		MPCon = Cast<AMain_Player_Controller>(GetWorld()->GetFirstPlayerController());
		if (MPCon)
		{
			MPCon->NewActorForMap(bIsStatic, GetOwner());
		}
	}

}

void UPointOfInterest_Component::SetUp(bool bAmIStatic, UTexture2D* Texture2d)
{
	bIsStatic = bAmIStatic;
	IconImage = Texture2d;
}



