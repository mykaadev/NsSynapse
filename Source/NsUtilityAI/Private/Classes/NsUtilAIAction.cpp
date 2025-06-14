// Copyright (C) 2024 mykaa. All rights reserved.

#include "Classes/NsUtilAIAction.h"
#include "Kismet/KismetMathLibrary.h"

UNsUtilAIAction::UNsUtilAIAction()
    : Score(0.f)
{}

float UNsUtilAIAction::GetScore() const
{
    return Score;
}

void UNsUtilAIAction::SetScore(const float InValue)
{
    Score = UKismetMathLibrary::NormalizeToRange(InValue, 0.f, 1.f);
}

void UNsUtilAIAction::ExecuteAction_Implementation(AActor* const InActor)
{
    // Override in children
}
