// Copyright (C) 2024 mykaa. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NsSynapseAction.generated.h"

/**
 * Synapse Utility AI - Base Action
 */
UCLASS(Blueprintable)
class NSSYNAPSE_API UNsSynapseAction : public UObject
{
    GENERATED_BODY()

// Functions
public:

    /** Constructor */
    UNsSynapseAction();

    /** Get the normalized action score */
    UFUNCTION(BlueprintCallable, Category = "NSUtilityAI")
    float GetScore() const;

    /** Set the action score */
    UFUNCTION(BlueprintCallable, Category = "NSUtilityAI")
    void SetScore(const float InValue);

    /** Execute the action */
    UFUNCTION(BlueprintNativeEvent, Category = "NSUtilityAI")
    void ExecuteAction(class AActor* InActor);
    virtual void ExecuteAction_Implementation(class AActor* const InActor);

// Variables
public:

    /** Considerations */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "NSUtilityAI")
    TArray<TSubclassOf<class UNsSynapseConsideration>> Considerations;

private:

    /** Action Score */
    UPROPERTY()
    float Score;
};