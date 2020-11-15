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

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "ForceObject", meta = (AllowPrivateAccess = "true"))
	UPrimitiveComponent* MyPrimComponent = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "HoverSettings", meta = (AllowPrivateAccess = "true"))
	float HoverLenght = 40.0f;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "HoverSettings", meta = (AllowPrivateAccess = "true"))
	float IncreaseHoverMultiplier = 2.0f;
	float OGHoverLenght = HoverLenght;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "HoverSettings", meta = (AllowPrivateAccess = "true"))
	float HoverMaxForce = 500000.0f;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "HoverSettings", meta = (AllowPrivateAccess = "true"))
	float LinearDamp = 1.0f;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "HoverSettings", meta = (AllowPrivateAccess = "true"))
	float AngularDamp = 2.0f;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "HoverSettings", meta = (AllowPrivateAccess = "true"))
	bool bIsHoverEnabled = true;

	bool HoverGrounded = false;
	FVector GroundNormal = FVector(0.0f);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	FCollisionQueryParams HoverCollParams;

public:	

	// Sets default values for this component's properties
	UHover_Component();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ChangeHoverState(bool HoverState);
	bool GetbIsHoverEnabled() { return bIsHoverEnabled; }

	void IncreaseHoverHeight();
	void DecreaseHoverHeight();

	bool AmIHovering() const;
	FVector GetGroundNormal() const;
		
};
