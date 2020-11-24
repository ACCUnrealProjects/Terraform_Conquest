//Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Hover_Component.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TERRAFORM_CONQUEST_API UHover_Component : public USceneComponent
{
	GENERATED_BODY()

private:
	
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "HoverSettings", meta = (AllowPrivateAccess = "true"))
	bool bIsHoverEnabled = true;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "HoverSettings", meta = (AllowPrivateAccess = "true"))
	float StablizationMulti = 1.0f; // best set between 0.0f and 2.0f

	bool HoverGrounded = false;
	FVector GroundNormal = FVector(0,0,1);


protected:

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "HoverSettings")
	float HoverMaxForce = 500000.0f;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "HoverSettings")
	float HoverLenght = 40.0f;
	float OGHoverLenght = HoverLenght;

	UPrimitiveComponent* MyPrimComponent = nullptr;
	FCollisionQueryParams HoverCollParams;

	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	// Sets default values for this component's properties
	UHover_Component();

	void SetUp(float HoverHeight, float MaxForce);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void HoverCalc();

	void ChangeHoverState(bool HoverState);
	bool GetbIsHoverEnabled() { return bIsHoverEnabled; }

	bool AmIHovering() const;
	FVector GetGroundNormal() const;
		
};
