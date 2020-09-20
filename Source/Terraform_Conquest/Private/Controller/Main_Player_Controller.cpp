// Alex Chatt Terraform_Conquest 2020

#include "../../Public/Controller/Main_Player_Controller.h"
#include "../../Public/Components/Health_Component.h"

AMain_Player_Controller::AMain_Player_Controller()
{

}

void AMain_Player_Controller::BeginPlay()
{
	Super::BeginPlay();

}

void AMain_Player_Controller::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		UHealth_Component* PawnHealthComp = InPawn->FindComponentByClass<UHealth_Component>();
		if (PawnHealthComp)
		{
			PawnHealthComp->IHaveDied.AddUniqueDynamic(this, &AMain_Player_Controller::MyPawnHasDied);
		}
	}
}

void AMain_Player_Controller::MyPawnHasDied()
{
	StartSpectatingOnly();
	//UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), true);
}