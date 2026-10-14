# NsSynapse Technical Documentation

## Architecture

One runtime module, `NsSynapse`.

| Class | Role |
|---|---|
| `UNsSynapseBrainComponent` | An actor component. It scores the action classes in `PossibleActions` and stores the best one. |
| `UNsSynapseAction` | A `Blueprintable` `UObject`. It holds a list of consideration classes and runs `ExecuteAction`. |
| `UNsSynapseConsideration` | A `Blueprintable` `UObject`. It returns a raw score from `CalculateScore` and maps it through `ConsiderationCurve`. |

Data flow for `ThinkAndReact`:

1. If `bBusy` is true, stop.
2. `ChooseAction` gets the CDO of each class in `PossibleActions`.
3. `ScoreAction` gets the CDO of each consideration and calls `GetScore(Owner)`.
4. `GetScore` clamps `CalculateScore` to 0..1, then evaluates `ConsiderationCurve`.
5. `ScoreAction` combines the consideration scores. It stores the result on the action with `SetScore`.
6. The action with the highest score above 0 becomes `BestAction`.
7. `ExecuteAction(Owner)` runs on `BestAction`.

### Score formula

For an action with N considerations:

```text
ModificationFactor = 1 - 1 / N
For each consideration score S (clamped 0..1):
    MakeUp = (1 - S) * ModificationFactor
    Final  = S + MakeUp * S
CombinedScore = product of all Final values
```

The make-up term stops one low score from removing an action too early when N is large. This is the common compensation factor for Utility AI.

## Lifetime

- The brain component does not tick (`bCanEverTick` is false). Game code calls `Think` or `ThinkAndReact`.
- Actions and considerations are never instanced. The brain uses their CDOs.
- `BestAction` holds a CDO pointer. It stays valid while the class is loaded.

## Extension Points

| Point | Use |
|---|---|
| `UNsSynapseConsideration::CalculateScore` | `BlueprintNativeEvent`. Return the raw score. |
| `UNsSynapseAction::ExecuteAction` | `BlueprintNativeEvent`. Run the behavior. |
| `UNsSynapseBrainComponent::Think` | Virtual. Override to change how the brain picks an action. |
| `UNsSynapseBrainComponent::ThinkAndReact` | Virtual. Override to change the busy rule or the run step. |

## Dependencies

Public: `Core`. Private: `CoreUObject`, `Engine`, `Slate`, `SlateCore`. No other studio plugin.

## Performance

- Cost is the number of actions times the number of considerations, for each `Think` call.
- There is no allocation in the scoring loop.
- Call `Think` on a timer or on an event, not every frame, when there are many agents.

## Networking

NsSynapse has no replication. Run the brain on the server for networked games, and replicate the result of the action.

## Testing

NsSynapse has no automated tests. Manual test path:

1. Make two actions with fixed-score considerations, for example 0.2 and 0.8.
2. Call `Think`. Make sure that `BestAction` is the 0.8 action.
3. Call `SetBusy(true)` and `ThinkAndReact`. Make sure that no action runs.

## Change Rules

- Keep `CalculateScore` and `ExecuteAction` signatures stable. Blueprint children depend on them.
- The shared CDO design is the main known limit. A change to instanced actions changes behavior for all projects. Document it as a breaking change.
- `UNsSynapseAction::SetScore` calls `NormalizeToRange(InValue, 0, 1)`. This returns the value unchanged and does not clamp it. Today all scores come in at 0..1, because the considerations clamp first.
- `UNsSynapseConsideration::Score` is not used today.
