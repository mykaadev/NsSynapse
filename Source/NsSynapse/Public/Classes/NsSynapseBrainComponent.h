// Copyright (C) 2025 mykaadev. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NsSynapseBrainComponent.generated.h"

/**
 * Synapse Utility AI - Brain Component
 * This component evaluates all Possible Actions call, using their considerations to pick the one with the highest utility score.
 */
UCLASS(ClassGroup=(UtilityAI), Blueprintable, meta=(BlueprintSpawnableComponent, DisplayName = "Utility AI Brain"))
class NSSYNAPSE_API UNsSynapseBrainComponent : public UActorComponent
{
    GENERATED_BODY()

// Functions
public:

    /** Constructor */
    UNsSynapseBrainComponent();

    /** Given an array of action classes, choose the one with the highest score */
    UFUNCTION(BlueprintCallable, Category = "NsSynapse")
    void ChooseAction(const TArray<TSubclassOf<class UNsSynapseAction>>& InActions);

    /**
     * Scores a given action by combining its considerations.
     * @param InAction - A UNsSynapseAction to evaluate.
     * @return The final utility score normalized between [0,1].
     */
    UFUNCTION(BlueprintCallable, Category = "NsSynapse")
    float ScoreAction(class UNsSynapseAction* const InAction) const;

    /** Returns the currently selected best Action */
    UFUNCTION(BlueprintCallable, Category = "NsSynapse")
    class UNsSynapseAction* GetBestAction() const;

    /** Think about what action is better to do at this given moment, this will overwrite our current BestAction */
    UFUNCTION(BlueprintCallable, Category = "NsSynapse")
    class UNsSynapseAction* Think();

    /** Think and react */
    UFUNCTION(BlueprintCallable, Category = "NsSynapse")
    void ThinkAndReact();

// Variables
public:

    /** Best action that was chosen */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NsSynapse")
    TObjectPtr<class UNsSynapseAction> BestAction;

    /**  List of action classes the brain can choose from */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NsSynapse")
    TArray<TSubclassOf<class UNsSynapseAction>> PossibleActions;
};