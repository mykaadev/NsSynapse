// Copyright (C) 2025 mykaadev. All rights reserved.

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
    UFUNCTION(BlueprintCallable, Category = "NsSynapse")
    float GetScore() const;

    /** Set the action score */
    UFUNCTION(BlueprintCallable, Category = "NsSynapse")
    void SetScore(const float InValue);

    /** Execute the action */
    UFUNCTION(BlueprintNativeEvent, Category = "NsSynapse")
    void ExecuteAction(class AActor* InActor);
    virtual void ExecuteAction_Implementation(class AActor* const InActor);

// Variables
public:

    /** Considerations */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "NsSynapse")
    TArray<TSubclassOf<class UNsSynapseConsideration>> Considerations;

private:

    /** Action Score */
    UPROPERTY()
    float Score;
};