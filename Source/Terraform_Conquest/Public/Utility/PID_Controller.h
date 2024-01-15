// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"

/**
 * Try and make this a template class so we dont have to have dups vars
 */
class TERRAFORM_CONQUEST_API PID_Controller
{
private:

	float gP, gI, gD;

	float fMin, fMax;
	float fIntegralCap = 1.0f;
	bool minMaxActive = false, firstTimeCal = true;


	float fIntegralStored;
	float fLastError;
	float fLastCurret;

	FVector vIntegralStored;
	FVector vLastError;
	FVector vLastCurret;

public:

	PID_Controller();

	void SetGains(float gainP, float gainI, float gainD);
	void SetMinMax(float Min, float Max);
	void SetIntergralCap(float intCap);

	float Calculate(float target, float current, float DT, bool bIsAngleValue);
	FVector Calculate(FVector target, FVector current, float DT);

	void Reset();
};
