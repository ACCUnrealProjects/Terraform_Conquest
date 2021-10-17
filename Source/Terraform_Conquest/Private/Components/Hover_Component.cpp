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

void UHover_Component::SetUp(float HoverHeight, float MaxForce)
{
	HoverLenght = HoverHeight;
	OGHoverLenght = HoverLenght;

	HoverMaxForce = MaxForce;
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
	FVector RayEnd = MyPos + (-GetOwner()->GetActorUpVector() * HoverLenght);

	FHitResult DownRayCast;

	HoverGrounded = false;
	if (GetWorld()->LineTraceSingleByChannel(DownRayCast, MyPos, RayEnd, ECollisionChannel::ECC_Visibility, HoverCollParams))
	{
		HoverGrounded = true;
		float DistanceToFoor = FVector::Dist(DownRayCast.Location, MyPos);
		float DistanceNormal = DistanceToFoor / HoverLenght;
		float ForceNeeded = FMath::Lerp(HoverMaxForce, 0.0f, DistanceNormal);
		FVector UpSpeedVector = MyPrimComponent->GetPhysicsLinearVelocity() * GetOwner()->GetActorUpVector();
		float StabSubForce = DefaultStabSubForce;
		if (DistanceNormal < HoverBoostThreshold)
		{
			StabSubForce = FMath::Lerp(StabSubForceLowerLerp, StabSubForceUpperLerp, 
				DistanceNormal / HoverBoostThreshold);
		}

		float Stablize = FMath::Sqrt(ForceNeeded) * (StabSubForce * StablizationMulti) * FMath::Max3(UpSpeedVector.X, UpSpeedVector.Y, UpSpeedVector.Z);
		float ForcetoApply = (ForceNeeded - Stablize);
		FVector ForceVector = GroundNormal * (ForcetoApply);
		MyPrimComponent->AddForce(ForceVector);

		GroundNormal = DownRayCast.ImpactNormal;
	}
}

void UHover_Component::ChangeHoverState(bool HoverState)
{
	bIsHoverEnabled = HoverState;
}

bool UHover_Component::AmIHovering() const
{
	return HoverGrounded;
}

FVector UHover_Component::GetGroundNormal() const
{
	return GroundNormal;
}