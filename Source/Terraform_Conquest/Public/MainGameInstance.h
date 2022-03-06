// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MainGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TERRAFORM_CONQUEST_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:


protected:

	virtual void Init() override;

	virtual void Shutdown() override;

	virtual void StartGameInstance() override;

public:


};
