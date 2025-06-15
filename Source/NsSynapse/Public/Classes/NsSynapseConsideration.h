// Copyright (C) 2024 mykaa. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Curves/Curvefloat.h"
#include "UObject/Object.h"
#include "NsSynapseConsideration.generated.h"

/**
 * Synapse Utility AI - Base Consideration
 */
UCLASS(Blueprintable)
class NSSYNAPSE_API UNsSynapseConsideration : public UObject
{
    GENERATED_BODY()

// Functions
public:

    /** Constructor */
    UNsSynapseConsideration();

    /** Get Score */
    UFUNCTION(BlueprintCallable, Category = "NSUtilityAI")
    float GetScore(class AActor* const InContext) const;

    /** Calculate Score */
    UFUNCTION(BlueprintNativeEvent, Category = "NSUtilityAI")
    float CalculateScore(class AActor* InOwner) const;
    virtual float CalculateScore_Implementation(class AActor* const InOwner) const;

private:

    /** Evaluate In curve */
    UFUNCTION(BlueprintCallable, Category = "NSUtilityAI")
    float EvaluateInCurve(const float InNormalizedScore) const;

// Variables
public:

    /** Consideration Curve */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "NSUtilityAI")
    FRuntimeFloatCurve ConsiderationCurve;

private:

    /** Consideration Score */
    UPROPERTY()
    float Score;
};