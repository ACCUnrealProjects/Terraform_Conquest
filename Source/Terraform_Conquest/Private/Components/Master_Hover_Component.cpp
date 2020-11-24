// Alex Chatt Terraform_Conquest 2020


#include "../../Public/Components/Master_Hover_Component.h"

// Called when the game starts
void UMaster_Hover_Component::BeginPlay()
{
	Super::BeginPlay();

	MyPrimComponent->SetLinearDamping(LinearDamp);
	MyPrimComponent->SetAngularDamping(AngularDamp);
}


void UMaster_Hover_Component::DampSetUp(float LinearD, float AngularD)
{
	LinearDamp = LinearD;
	AngularDamp = AngularD;

	MyPrimComponent->SetLinearDamping(LinearDamp);
	MyPrimComponent->SetAngularDamping(AngularDamp);
}


void UMaster_Hover_Component::IncreaseHoverHeight()
{
	HoverLenght *= IncreaseHoverMultiplier;
}

void UMaster_Hover_Component::DecreaseHoverHeight()
{
	HoverLenght = OGHoverLenght;
}
