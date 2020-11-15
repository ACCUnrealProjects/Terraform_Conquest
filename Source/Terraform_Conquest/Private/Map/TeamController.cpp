// Alex Chatt Terraform_Conquest 2020


#include "../../Public/Map/TeamController.h"

// Sets default values
ATeamController::ATeamController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATeamController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATeamController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

