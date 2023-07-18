// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "TerraformSpectatorPawn.generated.h"

/**
 * Default spectator pawn for the game
 */
UCLASS(config = Game, Blueprintable, BlueprintType)
class TERRAFORM_CONQUEST_API ATerraformSpectatorPawn : public ASpectatorPawn
{
	GENERATED_BODY()
	
private:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

public:
	ATerraformSpectatorPawn();

};
