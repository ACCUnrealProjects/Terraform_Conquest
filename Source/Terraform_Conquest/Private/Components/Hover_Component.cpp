//Alex Chatt Terraform_Conquest 2020

#include "../../Public/Components/Hover_Component.h"

// Sets default values for this component's properties
UHover_Component::UHover_Component()
{
	PrimaryComponentTick.bCanEverTick = true;

	SetVisibility(false);
}


// Called when the game starts
void UHover_Component::BeginPlay()
{
	Super::BeginPlay();

	OGHoverLenght = HoverLenght;
	MyPrimComponent = GetOwner()->FindComponentByClass<UPrimitiveComponent>();
	HoverCollParams.AddIgnoredActor(GetOwner());
}

void UHover_Component::SetUp(float HoverHeight)
{
	HoverLenght = HoverHeight;
	OGHoverLenght = HoverLenght;
}

// Called every frame
void UHover_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsHoverEnabled) { return; }

	HoverCalc();
}

void UHover_Component::HoverCalc()
{
	FVector MyPos = GetComponentLocation();
	FVector RayEnd = MyPos + (-GetUpVector() * HoverLenght);

	FHitResult DownRayCast;

	HoverGrounded = false;
	if (GetWorld()->LineTraceSingleByChannel(DownRayCast, MyPos, RayEnd, ECollisionChannel::ECC_Visibility, HoverCollParams))
	{
		HoverGrounded = true;
		FVector CV = MyPrimComponent->GetPhysicsLinearVelocityAtPoint(MyPos);
		FVector CF = CV.ProjectOnToNormal(GetUpVector());
		float DistanceNormal = 1.0f - (DownRayCast.Distance / HoverLenght);
		FVector NF = GetUpVector() * DistanceNormal * SupressionStiffness;
		FVector DF = NF - CF;

		MyPrimComponent->AddForceAtLocation(DF, MyPos);

		GroundNormal = DownRayCast.ImpactNormal;
	}
}

void UHover_Component::ChangeHoverState(bool HoverState)
{
	bIsHoverEnabled = HoverState;
}

void UHover_Component::IncreaseHoverHeight()
{
	HoverLenght *= IncreaseHoverMultiplier;
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