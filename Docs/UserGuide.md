# NsSynapse User Guide

## Purpose

NsSynapse is a Utility AI. An agent has a list of actions. Each action has considerations that give a score from 0 to 1. The agent picks the action with the highest combined score and runs it.

Use it for agents that weigh many factors, such as health, distance, and ammo. Do not use it for path finding, perception, or animation. It does not replace a Behavior Tree for long, ordered tasks.

## Setup

1. Copy the `NsSynapse` folder into the `Plugins` folder of your project.
2. Open the project and enable the plugin in **Edit > Plugins**.
3. For C++, add `"NsSynapse"` to the dependencies of your game module in its `Build.cs`.
4. Restart the editor.

The plugin needs no project settings. Its module runs on Win64, Mac, and Linux.

## Quick Start

### Blueprint

1. Make a child Blueprint of `NsSynapseConsideration`.
2. Override `Calculate Score`. Return a value from 0 to 1.
3. Make a child Blueprint of `NsSynapseAction`.
4. Override `Execute Action`. Put the behavior there.
5. In the action defaults, add the consideration class to **Considerations**.
6. Add the **Ns Synapse Brain** component to the AI actor.
7. Add the action class to **Possible Actions** on the component.
8. Call `Think And React` on the component, for example from a timer.

### C++

```cpp
#include "Classes/NsSynapseBrainComponent.h"
#include "Classes/NsSynapseConsideration.h"

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

1. Call `Think` on the brain component.
2. Read the return value, or call `Get Best Action`.
3. Run the action from your own code.

### Block a new decision while an action runs

1. Call `Set Busy` with **true** when a long action starts.
2. Call `Set Busy` with **false** when the action ends.

`Think And React` does nothing while the brain is busy. `Think` does not read the busy flag.

### Score a list of actions that is not on the component

1. Make an array of action classes.
2. Call `Choose Action` with the array.
3. Call `Get Best Action` to read the result.

### Shape a consideration

1. Open the consideration Blueprint and go to its class defaults.
2. Edit **Consideration Curve**. The X axis is the raw score. The Y axis is the final score.
3. To use a curve asset, set the external curve of **Consideration Curve** to a Float Curve asset.

### Read game state in a consideration or an action

1. Cast the actor input of `Calculate Score` or `Execute Action` to your actor class.
2. Read the values from that actor.

The input is the owner of the brain component.

## Settings

### Ns Synapse Brain component

| Setting | Default | Effect |
|---|---|---|
| **Possible Actions** | Empty | The action classes that `Think` and `Think And React` score. |
| **Best Action** | None | Read only. The action from the last choice. |
| **Busy** | false | Read only in the Details panel. While true, `Think And React` does nothing. Change it with `Set Busy`. |

### Ns Synapse Action

| Setting | Default | Effect |
|---|---|---|
| **Considerations** | Empty | The consideration classes that score this action. With no considerations, the action scores 1. |

### Ns Synapse Consideration

| Setting | Default | Effect |
|---|---|---|
| **Consideration Curve** | Line from (0, 0) to (1, 1) | Maps the raw score to the final score. |

## Debug

- Select the actor during play and read **Best Action** on the brain component in the Details panel.
- Call `Score Action` on one action to read its score.
- Call `Get Score` on an action to read the last score that a brain stored on it.

NsSynapse has no console commands, CVars, debug draw, or log category.

## Troubleshooting

| Problem | Cause | Fix |
|---|---|---|
| No action runs | All actions score 0, so **Best Action** is null. | Make sure that at least one consideration returns more than 0. |
| No action runs | The brain is busy. | Call `Set Busy` with **false** when the last action ends. |
| An action always wins | The action has no considerations, so it scores 1. | Add considerations to the action. |
| Data from one agent shows on another | All agents share the class default object of each action. | Keep per-agent data on the actor, not on the action. |
| The score ignores a value above 1 | The plugin clamps the raw score to 0..1. | Return a normalized value from `Calculate Score`. |

## Limits

- The brain uses the class default object (CDO) of each action and consideration. All agents share these objects.
- `Get Score` on an action returns the last score from any agent, because the CDO is shared.
- An action with a score of 0 is never chosen.
- If two actions have the same score, the first one in the list wins.
- An action with no considerations always scores 1.
- The brain component does not tick. Your game code must call `Think` or `Think And React`.
- The plugin does not replicate.
