// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class TERRAFORM_CONQUEST_API PID_Controller
{
private:

	float gP, gI, gD;

	float fMin, fMax;
	float fIntegral;
	float fLastProportional;

	FVector vIntegral;
	FVector vLastProportional;

	bool MinMaxActive;

public:

	PID_Controller();

	void SetGains(float gainP, float gainI, float gainD);
	void SetMinMax(float Min, float Max);

	float Calculate(float target, float current, float DT, bool bIsAngleValue);
	FVector Calculate(FVector target, FVector current, float DT);

	void Reset();
};
