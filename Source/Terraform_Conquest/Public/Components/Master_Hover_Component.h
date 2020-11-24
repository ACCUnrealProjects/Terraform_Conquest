// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/Hover_Component.h"
#include "Master_Hover_Component.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TERRAFORM_CONQUEST_API UMaster_Hover_Component : public UHover_Component
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "HoverSettings", meta = (AllowPrivateAccess = "true"))
	float LinearDamp = 1.0f;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "HoverSettings", meta = (AllowPrivateAccess = "true"))
	float AngularDamp = 2.0f;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "HoverSettings", meta = (AllowPrivateAccess = "true"))
	float IncreaseHoverMultiplier = 2.0f;
	
protected:

	virtual void BeginPlay() override;

public:

	void DampSetUp(float LinearD, float AngularD);

	void IncreaseHoverHeight();
	void DecreaseHoverHeight();

};
