// Copyright (C) 2025 nulled.softworks. All rights reserved.

#include "Classes/NsSynapseAction.h"
#include "Kismet/KismetMathLibrary.h"

UNsSynapseAction::UNsSynapseAction()
    : Score(0.f)
{}

float UNsSynapseAction::GetScore() const
{
    return Score;
}

void UNsSynapseAction::SetScore(const float InValue)
{
    Score = UKismetMathLibrary::NormalizeToRange(InValue, 0.f, 1.f);
}

void UNsSynapseAction::ExecuteAction_Implementation(AActor* const InActor)
{
    // Override in children
}
