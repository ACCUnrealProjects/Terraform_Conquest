// Alex Chatt Terraform_Conquest 2020

#include "Components/Tracks_Move_Component.h"

// Sets default values for this component's properties
UTracks_Move_Component::UTracks_Move_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}


// Called when the game starts
void UTracks_Move_Component::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UTracks_Move_Component::SetEngineSpeed(float NewEngineTrust)
{
	EngineThrust = NewEngineTrust;
	BackwardsEngineThrust = EngineThrust * 0.3f;
}

void UTracks_Move_Component::Forward(float Amount)
{

}

void UTracks_Move_Component::Turn(float Amount)
{

}

void UTracks_Move_Component::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	/*
	//Replacing Parent RequestDirectMove
	FVector AIDirection = MoveVelocity.GetSafeNormal();
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();

	// Use the dot product (cos) to see if we need to more forward of backward
	// If the angle between AIDirection and TankForward is < 90 then we will get a forward movement
	// if its more then 90 we will get a backward movement
	float ForwardProjection = FVector::DotProduct(AIDirection, TankForward);
	IntendMoveForward(ForwardProjection);

	//Use the cross product (sin) to get a vector perpendicular,
	//Then use the z vector (the up vector, in unreal this is z axis) to tell the tank
	//how to turn
	//(could also use dot product between the actor right vector and AIDirection)
	FVector CrossDir = FVector::CrossProduct(TankForward, AIDirection);
	IntendTurn(CrossDir.Z);
	*/
}