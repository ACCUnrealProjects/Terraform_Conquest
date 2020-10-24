// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class TERRAFORM_CONQUEST_API Tile
{
private:

	float TileSize = 200.0f; //cm

	float TileScale = 2.0f; //m
	
	bool Available = true;

	FVector Location = FVector(0);

public:
	Tile();
	~Tile();

	void SetAvailibity(bool NewAvailibity) { Available = NewAvailibity; }

	bool GetAvailbility() { return Available; }
};
