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

	OGHoverLenght = HoverLenght;

	MyPrimComponent = GetOwner()->FindComponentByClass<UPrimitiveComponent>();
	MyPrimComponent->SetLinearDamping(LinearDamp);
	MyPrimComponent->SetAngularDamping(AngularDamp);
	HoverCollParams.AddIgnoredActor(GetOwner());
}


// Called every frame
void UHover_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsHoverEnabled) { return; }

	FVector MyPos = GetComponentLocation();
	FVector RayEnd = MyPos + (-GetOwner()->GetActorUpVector() * HoverLenght);

	FHitResult DownRayCast;

	HoverGrounded = false;
	if (GetWorld()->LineTraceSingleByChannel(DownRayCast, MyPos, RayEnd, ECollisionChannel::ECC_Visibility, HoverCollParams))
	{
		HoverGrounded = true;
		float DistanceToFoor = FVector::Dist(DownRayCast.Location, MyPos);
		float DistanceNormal = DistanceToFoor / HoverLenght;
		float ForceNeeded = FMath::Lerp(HoverMaxForce, 0.0f, DistanceNormal);
		GroundNormal = DownRayCast.ImpactNormal;
		FVector UpSpeedVector = MyPrimComponent->GetPhysicsLinearVelocity() * GetOwner()->GetActorUpVector();
		float Stablize = FMath::Sqrt(ForceNeeded) * 2 * FMath::Max3(UpSpeedVector.X, UpSpeedVector.Y, UpSpeedVector.Z);
		float ForcetoApply = (ForceNeeded - Stablize);
		FVector ForceVector = GroundNormal * (ForcetoApply);
		MyPrimComponent->AddForce(ForceVector);
		//MyPrimComponent->AddForceAtLocation(ForceVector, GetComponentLocation());
	}

}

void UHover_Component::ChangeHoverState(bool HoverState)
{
	bIsHoverEnabled = HoverState;
}

void UHover_Component::IncreaseHoverHeight()
{
	HoverLenght = HoverLenght * IncreaseHoverMultiplier;
}

void UHover_Component::DecreaseHoverHeight()
{
	HoverLenght = OGHoverLenght;
}

bool UHover_Component::AmIHovering() const
{
	return HoverGrounded;
}

FVector UHover_Component::GetGroundNormal() const
{
	return GroundNormal;
}