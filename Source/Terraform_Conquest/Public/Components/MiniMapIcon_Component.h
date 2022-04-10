// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MiniMapIcon_Component.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TERRAFORM_CONQUEST_API UMiniMapIcon_Component : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	bool bIsStatic = false;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Image", meta = (AllowPrivateAccess = "true"))
	UTexture2D* IconImage = nullptr;

private:


protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	

	// Sets default values for this component's properties
	UMiniMapIcon_Component();

	void SetUp(bool bAmIStatic, UTexture2D* Texture2d);
};
