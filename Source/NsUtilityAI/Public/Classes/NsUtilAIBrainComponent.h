// Copyright (C) 2024 mykaa. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NsUtilAIBrainComponent.generated.h"

/**
 * Utility AI - Brain Component
 * This component evaluates all Possible Actions call, using their considerations to pick the one with the highest utility score.
 */
UCLASS(ClassGroup=(UtilityAI), Blueprintable, meta=(BlueprintSpawnableComponent, DisplayName = "Utility AI Brain"))
class NSUTILITYAI_API UNsUtilAIBrainComponent : public UActorComponent
{
    GENERATED_BODY()

// Functions
public:

    /** Constructor */
    UNsUtilAIBrainComponent();

    /** Given an array of action classes, choose the one with the highest score */
    UFUNCTION()
    void ChooseAction(const TArray<TSubclassOf<class UNsUtilAIAction>>& InActions);

    /**
     * Scores a given action by combining its considerations.
     * @param InAction - A UNsUtilAIAction to evaluate.
     * @return The final utility score normalized between [0,1].
     */
    UFUNCTION()
    float ScoreAction(class UNsUtilAIAction* const InAction);

    /** Returns the currently selected best Action */
    UFUNCTION()
    class UNsUtilAIAction* GetBestAction() const;

    /** Main entry—call this on a timer or via Tick to re-evaluate decision each frame or interval. */
    UFUNCTION(BlueprintCallable)
    void Think();

// Variables
public:

    /** Best action that was chosen */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<class UNsUtilAIAction> BestAction;

    /**  List of action classes the brain can choose from */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<TSubclassOf<class UNsUtilAIAction>> PossibleActions;
};