// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TeamsEnum.h"
#include "Control_Point.generated.h"

UCLASS()
class TERRAFORM_CONQUEST_API AControl_Point : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capture", meta = (AllowPrivateAccess = "true"))
	float CapPercentage = 0.0f;

	const float FullCap = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Capture", meta = (AllowPrivateAccess = "true"))
	float CapturePercentPerPerson = 1.0f;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Capture", meta = (AllowPrivateAccess = "true"))
    bool bBeingCaptured = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Points", meta = (AllowPrivateAccess = "true"))
	float CaptureTickTime = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Points", meta = (AllowPrivateAccess = "true"))
	int32 PointsPerTick = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Points", meta = (AllowPrivateAccess = "true"))
	float PointsTickTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capture Radius", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* CapturePointSphere = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* CapturePointFlag = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light", meta = (AllowPrivateAccess = "true"))
	class UPointLightComponent* CapturePointLight = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* CaptureIcon = nullptr;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Teams", meta = (AllowPrivateAccess = "true"))
	ETeam CurrentTeamControl = ETeam::Neutral;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Teams", meta = (AllowPrivateAccess = "true"))
	ETeam CurrentTeamCapturing = ETeam::Neutral;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teams", meta = (AllowPrivateAccess = "true"))
	TMap<ETeam, int32> Contesters;

	class AConquest_GameState* PlayingGameState = nullptr;

	FTimerHandle PointsTickTimer;

	FTimerHandle CaptureTickTimer;

private:

	UFUNCTION()
	void CapturingPoint();

	void CapturedPoint(ETeam TeamThatCaptured);

	UFUNCTION()
	void ScorePoints();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	AControl_Point();

};
