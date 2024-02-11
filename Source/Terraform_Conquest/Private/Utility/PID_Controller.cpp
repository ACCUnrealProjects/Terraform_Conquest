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
	minMaxActive = true;
}

void PID_Controller::SetIntergralCap(float intCap)
{
	fIntegralCap = intCap;
}

float PID_Controller::Calculate(float target, float current, float DT, bool bIsAngleValue)
{
	float P, D, I;
	float FinalValue;

	// Get the error
	float error = target - current;
	if (bIsAngleValue)
	{
		error = (((int32)error % 360) + 360) % 360;
		if (error < -180.0f)
		{
			error += 360.0f;
		}
		else if (error > 180.0f)
		{
			error -= 360.0f;
		}
	}
	// calculate P
	P = gP * error;

	// calculate I
	fIntegralStored = FMath::Clamp(fIntegralStored + (error * DT), -fIntegralCap, fIntegralCap);
	I = gI * fIntegralStored;

	// calculate D
	float errorChangeRate = (error - fLastError) / DT;
	fLastError = error;

	float rateOfChange = (current - fLastCurret);
	fLastCurret = current;

	float deriveMeasure = 0;
	if (!firstTimeCal)
	{
		if (bIsAngleValue)
		{
			deriveMeasure = errorChangeRate;
		}
		else
		{
			deriveMeasure = -rateOfChange;
		}
	}
	else
	{
		firstTimeCal = false;
	}
	D = gD * deriveMeasure;

	FinalValue = P + I + D;
	if (minMaxActive)
	{
		FinalValue = FMath::Clamp(FinalValue, fMin, fMax);
	}

	return FinalValue;
}

FVector PID_Controller::Calculate(FVector target, FVector current, float DT)
{
	FVector P, D, I;
	FVector FinalValue;

	// Get the error
	FVector error = target - current;
	// calculate P
	P = gP * error;

	// calculate I
	vIntegralStored = vIntegralStored + (error * DT);
	vIntegralStored = FinalValue.GetSafeNormal() * fIntegralCap;
	I = gI * vIntegralStored;

	// calculate D
	FVector errorChangeRate = (error - vLastError) / DT;
	vLastError = error;

	FVector rateOfChange = (current - vLastCurret) / DT;
	vLastCurret = current;

	FVector deriveMeasure = FVector::ZeroVector;
	if (!firstTimeCal)
	{
		deriveMeasure = errorChangeRate;
	}
	else
	{
		firstTimeCal = false;
	}
	D = gD * deriveMeasure;

	FinalValue = P + I + D;
	if (minMaxActive)
	{
		float VectorSize = FMath::Clamp(FinalValue.Size(), fMin, fMax);
		FinalValue = FinalValue.GetSafeNormal() * VectorSize;
	}

	return FinalValue;
}

void PID_Controller::Reset()
{
	fIntegralStored = fMin = fMax = fLastError = fLastCurret = 0.0f;
	vIntegralStored = vLastError = vLastCurret = FVector::ZeroVector;
	fIntegralCap = 1.0f;
	minMaxActive = false;
	firstTimeCal = true;
}
