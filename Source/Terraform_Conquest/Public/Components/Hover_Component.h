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

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "ForceObject", meta = (AllowPrivateAccess = "true"))
	UPrimitiveComponent* MyPrimComponent = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "HoverSettings", meta = (AllowPrivateAccess = "true"))
	float HoverLenght = 150.0f;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "HoverSettings", meta = (AllowPrivateAccess = "true"))
	float HoverMaxForce = 500000.0;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "HoverSettings", meta = (AllowPrivateAccess = "true"))
	float LinearDamp = 1.0f;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "HoverSettings", meta = (AllowPrivateAccess = "true"))
	float AngularDamp = 0.6f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	FCollisionQueryParams ShotParams;

public:	

	// Sets default values for this component's properties
	UHover_Component();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
