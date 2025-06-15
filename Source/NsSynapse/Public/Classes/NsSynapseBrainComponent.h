// Copyright (C) 2024 mykaa. All rights reserved.

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
    UFUNCTION(BlueprintCallable, Category = "NSUtilityAI")
    void ChooseAction(const TArray<TSubclassOf<class UNsSynapseAction>>& InActions);

    /**
     * Scores a given action by combining its considerations.
     * @param InAction - A UNsUtilAIAction to evaluate.
     * @return The final utility score normalized between [0,1].
     */
    UFUNCTION(BlueprintCallable, Category = "NSUtilityAI")
    float ScoreAction(class UNsSynapseAction* const InAction) const;

    /** Returns the currently selected best Action */
    UFUNCTION(BlueprintCallable, Category = "NSUtilityAI")
    class UNsSynapseAction* GetBestAction() const;

    /** Think about what action is better to do at this given moment, this will overwrite our current BestAction */
    UFUNCTION(BlueprintCallable, Category = "NSUtilityAI")
    class UNsSynapseAction* Think();

    /** Think and react */
    UFUNCTION(BlueprintCallable, Category = "NSUtilityAI")
    void ThinkAndReact();

// Variables
public:

    /** Best action that was chosen */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NSUtilityAI")
    TObjectPtr<class UNsSynapseAction> BestAction;

    /**  List of action classes the brain can choose from */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NSUtilityAI")
    TArray<TSubclassOf<class UNsSynapseAction>> PossibleActions;
};