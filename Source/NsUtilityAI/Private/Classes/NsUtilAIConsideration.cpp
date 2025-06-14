// Copyright (C) 2024 mykaa. All rights reserved.

#include "Classes/NsUtilAIConsideration.h"
#include "Curves/RichCurve.h"

UNsUtilAIConsideration::UNsUtilAIConsideration()
    : Score(0.f)
{
    if (ConsiderationCurve.EditorCurveData.IsEmpty())
    {
        ConsiderationCurve.EditorCurveData.AddKey(0.f, 0.f);
        ConsiderationCurve.EditorCurveData.AddKey(1.f, 1.f);
    }
}

float UNsUtilAIConsideration::GetScore(AActor* InContext) const
{
    // Raw score from subclass logic
    const float RawScore = CalculateScore(InContext);

    // Clamp the raw score to ensure it’s normalized before curve evaluation
    const float NormalizedScore = FMath::Clamp(RawScore, 0.f, 1.f);

    // Evaluate through the user-defined response curve
    return EvaluateInCurve(NormalizedScore);
}

float UNsUtilAIConsideration::CalculateScore_Implementation(class AActor* const InOwner) const
{
    // Override in children
    return 0.f;
}

float UNsUtilAIConsideration::EvaluateInCurve(const float InNormalizedScore) const
{
    const FRichCurve* const RichCurve = ConsiderationCurve.GetRichCurveConst();
    if (RichCurve != nullptr)
    {
        return RichCurve->Eval(InNormalizedScore);
    }

    return 0.f;
}
