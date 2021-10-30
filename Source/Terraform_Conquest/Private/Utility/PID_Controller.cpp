// Alex Chatt Terraform_Conquest 2020


#include "Utility/PID_Controller.h"

PID_Controller::PID_Controller()
{
	Reset();
}

void PID_Controller::SetGains(float gainP, float gainI, float gainD)
{
	gP = gainP;
	gI = gainI;
	gD = gainD;
}

void PID_Controller::SetMinMax(float Min, float Max)
{
	fMin = Min;
	fMax = Max;
	MinMaxActive = true;
}

float PID_Controller::Calculate(float target, float current, float DT)
{
	// Get the error
	float proportional = target - current;
	float derivitive = (proportional - fLastProportional) / DT;
	// store last error after using for derivitive
	fLastProportional = proportional;
	fIntegral += proportional * DT;

	float FinalValue = gP * proportional + gD * derivitive + gI * fIntegral;

	if (MinMaxActive)
	{
		FinalValue = FMath::Clamp(FinalValue, fMin, fMax);
	}

	return FinalValue;
}

FVector PID_Controller::Calculate(FVector target, FVector current, float DT)
{
	// Get the error
	FVector proportional = target - current;
	FVector derivitive = (proportional - vLastProportional) / DT;
	// store last error after using for derivitive
	vLastProportional = proportional;
	vIntegral += proportional * DT;

	FVector FinalValue = gP * proportional + gD * derivitive + gI * vIntegral;

	if (MinMaxActive)
	{
		float VectorSize = FMath::Clamp(FinalValue.Size(), fMin, fMax);
		FinalValue = FinalValue.GetSafeNormal() * VectorSize;
	}

	return FinalValue;
}

void PID_Controller::Reset()
{
	fIntegral = fMin = fMax = fLastProportional = 0.0f;
	vIntegral = vLastProportional = FVector::ZeroVector;
	MinMaxActive = false;
}
