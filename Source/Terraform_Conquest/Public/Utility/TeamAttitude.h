// Alex Chatt Terraform_Conquest 2020
// https://forums.unrealengine.com/t/how-do-i-use-the-ai-perception-teams/120837/2

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "TeamAttitude.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FTeamAttitude
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        TArray<TEnumAsByte<ETeamAttitude::Type>> Attitude;

    FTeamAttitude() {};

    FTeamAttitude(std::initializer_list<TEnumAsByte<ETeamAttitude::Type>> attitudes) :
        Attitude(std::move(attitudes))
    { };
};