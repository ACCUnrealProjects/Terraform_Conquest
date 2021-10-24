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
	float SupressionStiffness = 1.0f;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "HoverSettings", meta = (AllowPrivateAccess = "true"))
	float HoverLenght = 40.0f;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "HoverSettings", meta = (AllowPrivateAccess = "true"))
	float IncreaseHoverMultiplier = 2.0f;

	float OGHoverLenght = HoverLenght;

	UPrimitiveComponent* MyPrimComponent = nullptr;
	FCollisionQueryParams HoverCollParams;

	bool HoverGrounded = false;
	FVector GroundNormal = FVector(0,0,1);


protected:

	// Called when the game starts
	virtual void BeginPlay() override; 
	 
public:	

	// Sets default values for this component's properties
	UHover_Component();

	void SetUp(float HoverHeight);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void HoverCalc();

	void ChangeHoverState(bool HoverState);
	void IncreaseHoverHeight();
	void DecreaseHoverHeight();

	bool GetbIsHoverEnabled() const { return bIsHoverEnabled; }
	bool AmIHovering() const;
	FVector GetGroundNormal() const;
};
