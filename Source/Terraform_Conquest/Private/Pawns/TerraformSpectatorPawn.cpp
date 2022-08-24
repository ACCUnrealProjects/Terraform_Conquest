// Alex Chatt Terraform_Conquest 2020

#include "Pawns/TerraformSpectatorPawn.h"

ATerraformSpectatorPawn::ATerraformSpectatorPawn()
{
	bReplicates = false;
}

void ATerraformSpectatorPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &ADefaultPawn::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &ADefaultPawn::MoveRight);
	PlayerInputComponent->BindAxis("Up", this, &ADefaultPawn::MoveUp_World);
	PlayerInputComponent->BindAxis("LookRight", this, &ADefaultPawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ADefaultPawn::AddControllerPitchInput);
}

