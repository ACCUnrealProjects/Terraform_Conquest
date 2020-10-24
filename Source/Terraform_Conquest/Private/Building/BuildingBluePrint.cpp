// Alex Chatt Terraform_Conquest 2020


#include "../../Public/Building/BuildingBluePrint.h"
#include "Components/BoxComponent.h"

// Sets default values
ABuildingBluePrint::ABuildingBluePrint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABuildingBluePrint::BeginPlay()
{
	Super::BeginPlay();

	OverlapSpace->OnComponentBeginOverlap.AddDynamic(this, &ABuildingBluePrint::OnOverlapBegin);
	OverlapSpace->OnComponentEndOverlap.AddDynamic(this, &ABuildingBluePrint::OnOverlapEnd);
}

// Called every frame
void ABuildingBluePrint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABuildingBluePrint::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void ABuildingBluePrint::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}