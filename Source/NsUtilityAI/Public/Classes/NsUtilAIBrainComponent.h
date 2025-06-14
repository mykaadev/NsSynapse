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
    UFUNCTION(BlueprintCallable, Category = "NSUtilityAI")
    void ChooseAction(const TArray<TSubclassOf<class UNsUtilAIAction>>& InActions);

    /**
     * Scores a given action by combining its considerations.
     * @param InAction - A UNsUtilAIAction to evaluate.
     * @return The final utility score normalized between [0,1].
     */
    UFUNCTION(BlueprintCallable, Category = "NSUtilityAI")
    float ScoreAction(class UNsUtilAIAction* const InAction) const;

    /** Returns the currently selected best Action */
    UFUNCTION(BlueprintCallable, Category = "NSUtilityAI")
    class UNsUtilAIAction* GetBestAction() const;

    /** Think about what action is better to do at this given moment, this will overwrite our current BestAction */
    UFUNCTION(BlueprintCallable, Category = "NSUtilityAI")
    class UNsUtilAIAction* Think();

    /** Think and react */
    UFUNCTION(BlueprintCallable, Category = "NSUtilityAI")
    void ThinkAndReact();

// Variables
public:

    /** Best action that was chosen */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NSUtilityAI")
    TObjectPtr<class UNsUtilAIAction> BestAction;

    /**  List of action classes the brain can choose from */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NSUtilityAI")
    TArray<TSubclassOf<class UNsUtilAIAction>> PossibleActions;
};