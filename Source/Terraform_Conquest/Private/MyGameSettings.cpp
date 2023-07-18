// Alex Chatt Terraform_Conquest 2020

#include "MyGameSettings.h"

UMyGameSettings::UMyGameSettings(const FObjectInitializer& ObjectInitializer)
{
    typedef ETeamAttitude::Type EA;
    TeamAttitudes = {
        {EA::Neutral, EA::Neutral,  EA::Neutral,  EA::Neutral,  EA::Neutral },//Neutral
        {EA::Neutral, EA::Friendly, EA::Hostile,  EA::Friendly, EA::Hostile},//Team1
        {EA::Neutral, EA::Hostile,  EA::Friendly, EA::Hostile,  EA::Hostile},//Team2
        {EA::Neutral, EA::Friendly, EA::Hostile,  EA::Friendly, EA::Friendly },//Team3
        {EA::Neutral, EA::Hostile,  EA::Hostile,  EA::Friendly, EA::Friendly }//Team4
    };
}

const UMyGameSettings* UMyGameSettings::Get()
{
    return GetDefault<UMyGameSettings>();
}

ETeamAttitude::Type UMyGameSettings::GetAttitude(FGenericTeamId Of, FGenericTeamId Towards)
{
    const TArray<FTeamAttitudeSystem>& teamAttitudes = UMyGameSettings::Get()->TeamAttitudes;
    bool ofValid = teamAttitudes.IsValidIndex(Of.GetId());
    bool towardsValid = teamAttitudes.IsValidIndex(Towards.GetId());

    if (ofValid && towardsValid)
    {
        const TArray<TEnumAsByte<ETeamAttitude::Type>>& attitudes = teamAttitudes[Of.GetId()].Attitude;
        if (attitudes.IsValidIndex(Towards.GetId()))
        {
            return attitudes[Towards.GetId()];
        }
    }
    return ETeamAttitude::Neutral;
}