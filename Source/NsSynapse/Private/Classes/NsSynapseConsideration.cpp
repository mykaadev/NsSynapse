// Copyright (C) 2025 nulled.softworks. All rights reserved.

#include "Classes/NsSynapseConsideration.h"
#include "Curves/RichCurve.h"

UNsSynapseConsideration::UNsSynapseConsideration()
    : Score(0.f)
{
    if (ConsiderationCurve.EditorCurveData.IsEmpty())
    {
        ConsiderationCurve.EditorCurveData.AddKey(0.f, 0.f);
        ConsiderationCurve.EditorCurveData.AddKey(1.f, 1.f);
    }
}

float UNsSynapseConsideration::GetScore(AActor* InContext) const
{
    // Raw score from subclass logic
    const float RawScore = CalculateScore(InContext);

    // Clamp the raw score to ensure it’s normalized before curve evaluation
    const float NormalizedScore = FMath::Clamp(RawScore, 0.f, 1.f);

    // Evaluate through the user-defined response curve
    return EvaluateInCurve(NormalizedScore);
}

float UNsSynapseConsideration::CalculateScore_Implementation(class AActor* const InOwner) const
{
    // Override in children
    return 0.f;
}

float UNsSynapseConsideration::EvaluateInCurve(const float InNormalizedScore) const
{
    const FRichCurve* const RichCurve = ConsiderationCurve.GetRichCurveConst();
    if (RichCurve != nullptr)
    {
        return RichCurve->Eval(InNormalizedScore);
    }

    return 0.f;
}
