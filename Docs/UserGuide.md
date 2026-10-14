# NsSynapse User Guide

## Purpose

NsSynapse is a small Utility AI framework. An agent has a list of actions. Each action has considerations that give a score from 0 to 1. The agent runs the action with the highest score.

Use it for agents that weigh many factors, such as health, distance, and ammo. Do not use it for path finding, perception, or animation. It does not replace a Behavior Tree for long, ordered tasks.

## Setup

1. Add `NsSynapse` to the `Plugins` list of the `.uproject` file.
2. For C++, add `"NsSynapse"` to the module dependencies in `Build.cs`.

## Quick Start

### Blueprint

1. Add a `NsSynapseBrainComponent` to the AI actor.
2. Make a Blueprint child of `NsSynapseConsideration`. Override `Calculate Score`. Return a value from 0 to 1.
3. Make a Blueprint child of `NsSynapseAction`. Override `Execute Action`. Add the consideration to `Considerations`.
4. Add the action class to `Possible Actions` on the brain component.
5. Call `Think And React` when the agent must decide, for example on a timer.

### C++

```cpp
// A consideration that prefers low health
UCLASS()
class UMyLowHealthConsideration : public UNsSynapseConsideration
{
    GENERATED_BODY()

public:
    virtual float CalculateScore_Implementation(AActor* const InOwner) const override
    {
        const AMyBot* const Bot = Cast<AMyBot>(InOwner);
        return Bot != nullptr ? 1.f - Bot->GetHealthPercent() : 0.f;
    }
};

// Decide and act
Brain->ThinkAndReact();
```

## Common Tasks

### Decide without acting

Call `Think`. It returns the best action and stores it in `BestAction`. Run the action yourself.

### Block a new decision while an action runs

1. Call `SetBusy(true)` when a long action starts.
2. Call `SetBusy(false)` when it ends.

`ThinkAndReact` does nothing while the brain is busy.

### Shape a consideration

Edit `Consideration Curve` on the consideration. The X axis is the raw score. The Y axis is the final score. The default curve is linear from (0, 0) to (1, 1).

## Rules

- Return a value from 0 to 1 from `CalculateScore`. The plugin clamps other values.
- Keep actions and considerations stateless. The brain uses the class default object of each class. See Limits.
- Read game state from the actor that `CalculateScore` and `ExecuteAction` receive.
- Call `Think` or `ThinkAndReact` from game code. The brain does not tick.

## Settings

| Property | Owner | Effect |
|---|---|---|
| `PossibleActions` | Brain component | The action classes that the brain scores. |
| `Considerations` | Action | The consideration classes that score the action. |
| `ConsiderationCurve` | Consideration | The response curve applied to the raw score. |

## Debug

- Read `BestAction` on the brain component in the Details panel during play.
- Call `ScoreAction` on one action to see its score.

NsSynapse has no console commands or log category.

## Limits

- The brain uses the class default object (CDO) of each action and consideration. All agents share these objects. Do not store per-agent data on them.
- `GetScore` on an action returns the last score from any agent, because the CDO is shared.
- An action with a score of 0 is never chosen. If all actions score 0, `BestAction` is null.
- If two actions have the same score, the first one in `PossibleActions` wins.
- An action with no considerations always scores 1.
