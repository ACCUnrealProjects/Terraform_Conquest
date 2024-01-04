//Alex Chatt Terraform_Conquest 2020

#include "Components/Hover_Component.h"

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

	HoverPid.SetMinMax(-1.0f, 1.0f);
	HoverPid.SetGains(0.8f, 0.0002f, 0.2f);

}

void UHover_Component::SetUp(float HoverHeight, float SupressionStiff, float Dampmulti)
{
	HoverLenght = HoverHeight;
	OGHoverLenght = HoverLenght;
	SupressionStiffness = SupressionStiff;
	Dampening = Dampmulti;
}

// Called every frame
void UHover_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsHoverEnabled || 
		!Cast<APawn>(GetOwner())->IsLocallyControlled())
	{ 
		return; 
	}

	HoverCalc();

	if (IncreasingHover)
	{
		HoverLenght = FMath::FInterpTo(HoverLenght, OGHoverLenght * IncreaseHoverMultiplier,
			DeltaTime, 2.0f);
	}
	else
	{
		HoverLenght = FMath::FInterpTo(HoverLenght, OGHoverLenght, DeltaTime, 2.0f);
	}
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
		// Get current velocity at point
		FVector CV = MyPrimComponent->GetPhysicsLinearVelocityAtPoint(MyPos);
		// project onto the up vector for the hover comp
		FVector CF = CV.ProjectOnToNormal(GetUpVector()) * Dampening;
		// see how far we are off the ground
		float DistanceNormal = 1.0f - (DownRayCast.Distance / HoverLenght);
		// Get a counter-acting up force
		FVector NF = GetUpVector() * DistanceNormal * SupressionStiffness;
		if (DownRayCast.Distance > OGHoverLenght) 
		{
			NF = GetUpVector() * DistanceNormal * (SupressionStiffness/2);
		}
		// get what we want the new vel to be for the point
		// Times by the mass to be mass independent
		FVector DF = (NF - CF) * MyPrimComponent->GetMass();

		// Apply the force
		MyPrimComponent->AddForce(DF);

		GroundNormal = DownRayCast.ImpactNormal;
	}
}

void UHover_Component::HoverCalcPid(float DT)
{
	FVector MyPos = GetComponentLocation();
	FVector RayEnd = MyPos + (-GetUpVector() * HoverLenght);

	FHitResult DownRayCast;

	HoverGrounded = false;
	if (GetWorld()->LineTraceSingleByChannel(DownRayCast, MyPos, RayEnd, ECollisionChannel::ECC_Visibility, HoverCollParams))
	{
		HoverGrounded = true;
		//Get percentage of force to add
		float ForcePercentage = HoverPid.Calculate(HoverLenght, DownRayCast.Distance, DT, false);
		float ForceToAdd = SupressionStiffness * ForcePercentage * MyPrimComponent->GetMass();
		// Apply the force
		MyPrimComponent->AddForce(ForceToAdd * GetUpVector());
		GroundNormal = DownRayCast.ImpactNormal;
	}
}

void UHover_Component::ChangeHoverState(bool HoverState)
{
	bIsHoverEnabled = HoverState;
}

void UHover_Component::IncreaseHoverHeight()
{
	IncreasingHover = true;
}

void UHover_Component::DecreaseHoverHeight()
{
	IncreasingHover = false;
}

bool UHover_Component::AmIHovering() const
{
	return HoverGrounded;
}

FVector UHover_Component::GetGroundNormal() const
{
	return GroundNormal;
}