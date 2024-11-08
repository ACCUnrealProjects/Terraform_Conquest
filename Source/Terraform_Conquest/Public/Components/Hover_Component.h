//Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Utility/PID_Controller.h"
#include "Hover_Component.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TERRAFORM_CONQUEST_API UHover_Component : public USceneComponent
{
	GENERATED_BODY()

private:
	
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "HoverSettings", meta = (AllowPrivateAccess = "true"))
	bool bIsHoverEnabled = true;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "HoverSettings", meta = (AllowPrivateAccess = "true"))
	float SupressionStiffness = 1280.0f;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "HoverSettings", meta = (AllowPrivateAccess = "true"))
	float Dampening = 1.0f;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "HoverSettings", meta = (AllowPrivateAccess = "true"))
	float HoverLenght = 40.0f;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "HoverSettings", meta = (AllowPrivateAccess = "true"))
	float IncreaseHoverMultiplier = 2.0f;

	float OGHoverLenght = HoverLenght;

	UPrimitiveComponent* MyPrimComponent = nullptr;
	FCollisionQueryParams HoverCollParams;

	bool HoverGrounded = false;
	bool IncreasingHover = false;
	FVector GroundNormal = FVector(0,0,1);

	PID_Controller HoverPid;


protected:

	// Called when the game starts
	virtual void BeginPlay() override; 
	 
public:	

	// Sets default values for this component's properties
	UHover_Component();

	void SetUp(float HoverHeight, float SupressionStiff, float Dampmulti);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void HoverCalc();
	void HoverCalcPid(float DT);

	void ChangeHoverState(bool HoverState);
	void IncreaseHoverHeight();
	void DecreaseHoverHeight();
	
	bool GetbIsHoverEnabled() const { return bIsHoverEnabled; }
	bool AmIHovering() const;
	float GetHoverLenght() const { return HoverLenght; }
	FVector GetGroundNormal() const;
};
