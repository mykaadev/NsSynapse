// Copyright (C) 2024 mykaa. All rights reserved.

#include "Classes/NsSynapseBrainComponent.h"
#include "Classes/NsSynapseAction.h"
#include "Classes/NsSynapseConsideration.h"

UNsSynapseBrainComponent::UNsSynapseBrainComponent()
    : BestAction(nullptr)
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UNsSynapseBrainComponent::ChooseAction(const TArray<TSubclassOf<UNsSynapseAction>>& InActions)
{
    BestAction = nullptr;

    // If there are no actions, do nothing
    if (InActions.Num() == 0)
    {
        return;
    }

    float BestScore = 0.f;

    // Loop through each action, score it, and pick the highest
    for (const TSubclassOf<UNsSynapseAction>& ActionClass : InActions)
    {
        if (ActionClass == nullptr)
        {
            continue;
        }

        if (UNsSynapseAction* const Action = ActionClass->GetDefaultObject<UNsSynapseAction>())
        {
            // Compute this action's score
            const float CurrentScore = ScoreAction(Action);

            if (CurrentScore > BestScore)
            {
                BestScore = CurrentScore;
                BestAction = Action;
            }
        }
    }
}

float UNsSynapseBrainComponent::ScoreAction(UNsSynapseAction* const InAction) const
{
    // If action is null, score zero
    if (InAction == nullptr)
    {
        return 0.f;
    }

    // Get the list of consideration classes from this action
    const TArray<TSubclassOf<UNsSynapseConsideration>>& ActionConsiderations = InAction->Considerations;
    const int32 NumConsiderations = ActionConsiderations.Num();
    if (NumConsiderations == 0)
    {
        // No considerations means the action is fully desirable.
        InAction->SetScore(1.f);
        return 1.f;
    }

    // (N-1)/N = tempering factor: ensures that one low consideration doesn't completely kill the final score too early
    const float ModificationFactor = 1.f - (1.f / static_cast<float>(NumConsiderations));
    float CombinedScore = 1.f;

    // Iterate each consideration, multiply in its final value
    for (const TSubclassOf<UNsSynapseConsideration>& Consideration : ActionConsiderations)
    {
        // Skip invalid entries
        if (Consideration == nullptr || GetOwner() == nullptr)
        {
            continue;
        }

        if (const UNsSynapseConsideration* const ConsiderationCDO = Consideration->GetDefaultObject<UNsSynapseConsideration>())
        {
            // Evaluate: Designers can implement GetScore to sample the curve based state
            const float RawScore = ConsiderationCDO->GetScore(GetOwner());

            // We assume RawScore is between 0 and 1. If not, clamp it
            const float NormalizedScore = FMath::Clamp(RawScore, 0.f, 1.f);

            // “Make up” term ensures a single low consideration doesn't collapse to zero immediately
            const float MakeUpValue = (1.f - NormalizedScore) * ModificationFactor;
            const float FinalConsiderationScore = NormalizedScore + (MakeUpValue * NormalizedScore);
            CombinedScore *= FinalConsiderationScore;
        }
    }

    // Store final normalized score back into the action object
    InAction->SetScore(CombinedScore);
    return InAction->GetScore();
}

UNsSynapseAction* UNsSynapseBrainComponent::GetBestAction() const
{
    return BestAction;
}

UNsSynapseAction* UNsSynapseBrainComponent::Think()
{
    // Each time Think() runs, we re-evaluate all possible actions
    ChooseAction(PossibleActions);
    return GetBestAction();
}

void UNsSynapseBrainComponent::ThinkAndReact()
{
    Think(); // Each time Think() runs, we re-evaluate all possible actions

    // Automatically execute the action
    if (BestAction != nullptr && GetOwner() != nullptr)
    {
        BestAction->ExecuteAction(GetOwner());
    }
}
