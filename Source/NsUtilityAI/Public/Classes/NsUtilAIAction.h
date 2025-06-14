// Copyright (C) 2024 mykaa. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NsUtilAIAction.generated.h"

/**
 * Base Action for Utility AI
 */
UCLASS(Blueprintable)
class NSUTILITYAI_API UNsUtilAIAction : public UObject
{
    GENERATED_BODY()

// Functions
public:

    /** Constructor */
    UNsUtilAIAction();

    /** Get the normalized action score */
    UFUNCTION(BlueprintCallable)
    float GetScore() const;

    /** Set the action score */
    UFUNCTION(BlueprintCallable)
    void SetScore(const float InValue);

    /** Execute the action */
    UFUNCTION(BlueprintNativeEvent)
    void ExecuteAction(class AActor* InActor);
    virtual void ExecuteAction_Implementation(class AActor* const InActor);

// Variables
public:

    /** Considerations */
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<TSubclassOf<class UNsUtilAIConsideration>> Considerations;

private:

    /** Action Score */
    UPROPERTY()
    float Score;
};