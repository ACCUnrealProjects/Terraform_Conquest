//Alex Chatt Terraform_Conquest 2020

#include "../../Public/Components/Hover_Component.h"

// Sets default values for this component's properties
UHover_Component::UHover_Component()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UHover_Component::BeginPlay()
{
	Super::BeginPlay();

	MyPrimComponent = GetOwner()->FindComponentByClass<UPrimitiveComponent>();
	MyPrimComponent->SetLinearDamping(LinearDamp);
	MyPrimComponent->SetAngularDamping(AngularDamp);
	ShotParams.AddIgnoredActor(GetOwner());
}


// Called every frame
void UHover_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector MyPos = GetComponentLocation();
	FVector RayEnd = MyPos + (-GetOwner()->GetActorUpVector() * HoverLenght);

	FHitResult DownRayCast;

	if (GetWorld()->LineTraceSingleByChannel(DownRayCast, MyPos, RayEnd, ECollisionChannel::ECC_Camera, ShotParams))
	{
		float DistanceToFoor = FVector::Dist(DownRayCast.Location, MyPos);
		float DistanceNormal = DistanceToFoor / HoverLenght;
		float ForceNeeded = FMath::Lerp(HoverMaxForce, 0.0f, DistanceNormal);

		FVector ForceVector = DownRayCast.ImpactNormal * ForceNeeded;
		MyPrimComponent->AddForce(ForceVector);
	}

}

