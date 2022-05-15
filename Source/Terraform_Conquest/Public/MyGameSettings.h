// Alex Chatt Terraform_Conquest 2020
// https://forums.unrealengine.com/t/how-do-i-use-the-ai-perception-teams/120837/2
#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Utility/TeamAttitude.h"
#include "GenericTeamAgentInterface.h"
#include "MyGameSettings.generated.h"

/**
 * 
 */
UCLASS(Config=Game)
class TERRAFORM_CONQUEST_API UMyGameSettings : public UDeveloperSettings
{
    GENERATED_BODY()

public:

    UPROPERTY(Category = "Artificial Intelligence", EditAnywhere, BlueprintReadOnly, Config)
       TArray<FTeamAttitude> TeamAttitudes;

public:

    UMyGameSettings(const FObjectInitializer& ObjectInitializer);

    static const UMyGameSettings* Get();

    UFUNCTION(Category = "Artificial Intelligence", BlueprintPure)
       static ETeamAttitude::Type GetAttitude(FGenericTeamId Of, FGenericTeamId Towards);
	
};
