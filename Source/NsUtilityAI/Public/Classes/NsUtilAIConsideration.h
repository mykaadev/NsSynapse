// Copyright (C) 2024 mykaa. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NsUtilAIConsideration.generated.h"

/**
 * Base Consideration for Utility AI
 */
UCLASS(Blueprintable)
class NSUTILITYAI_API UNsUtilAIConsideration : public UObject
{
    GENERATED_BODY()

// Functions
public:

    /** Constructor */
    UNsUtilAIConsideration();

    /** Get Score */
    UFUNCTION()
    float GetScore(class AActor* const InContext) const;

    /** Calculate Score */
    UFUNCTION(BlueprintNativeEvent)
    float CalculateScore(class AActor* InOwner) const;
    virtual float CalculateScore_Implementation(class AActor* const InOwner) const;

private:

    /** Evaluate In curve */
    UFUNCTION()
    float EvaluateInCurve(float InNormalizedScore) const;

// Variables
public:

    /** Consideration Curve */
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FRuntimeFloatCurve ConsiderationCurve;

private:

    /** Consideration Score */
    UPROPERTY()
    float Score;
};