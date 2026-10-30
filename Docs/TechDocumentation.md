# NsSynapse Technical Documentation

## Architecture

### Modules

| Module | Type | Loading Phase | Platforms | Content |
|---|---|---|---|---|
| `NsSynapse` | Runtime | Default | Linux, Mac, Win64 | The brain component, the action base class, and the consideration base class. |

`FNsSynapseModule` has empty `StartupModule` and `ShutdownModule` functions. The plugin has no `Content/` folder.

### Folders

| Folder | Files |
|---|---|
| `Source/NsSynapse/Public` | `NsSynapse.h` (module class) |
| `Source/NsSynapse/Public/Classes` | `NsSynapseBrainComponent.h`, `NsSynapseAction.h`, `NsSynapseConsideration.h` |
| `Source/NsSynapse/Private` | `NsSynapse.cpp` |
| `Source/NsSynapse/Private/Classes` | The `.cpp` file of each class |

Include the headers with the `Classes/` prefix, for example `#include "Classes/NsSynapseBrainComponent.h"`.

### Main Classes

| Class | Responsibility |
|---|---|
| `UNsSynapseBrainComponent` | `UActorComponent`, `Blueprintable`, `BlueprintSpawnableComponent`, class group `UtilityAI`. It scores the action classes in `PossibleActions` and stores the best one in `BestAction`. |
| `UNsSynapseAction` | `Blueprintable` `UObject`. It holds `Considerations` (consideration classes) and a private `Score`. It runs `ExecuteAction`. |
| `UNsSynapseConsideration` | `Blueprintable` `UObject`. It returns a raw score from `CalculateScore` and maps it through `ConsiderationCurve` (`FRuntimeFloatCurve`). |

### Data Flow

`ThinkAndReact` runs these steps on the calling thread:

1. If `bBusy` is true, the function returns.
2. `Think` calls `ChooseAction(PossibleActions)`.
3. `ChooseAction` sets `BestAction` to null. For each valid class, it gets the class default object (CDO) and calls `ScoreAction`.
4. `ScoreAction` gets the CDO of each consideration class and calls `GetScore(GetOwner())`.
5. `GetScore` clamps `CalculateScore` to 0..1 and evaluates the curve with `FRichCurve::Eval`.
6. `ScoreAction` clamps the curve result to 0..1, applies the make-up term, and multiplies the results.
7. `ScoreAction` stores the product on the action CDO with `SetScore`.
8. An action becomes `BestAction` only if its score is strictly greater than the best score so far. The best score starts at 0.
9. If `BestAction` and the owner are valid, `ExecuteAction(GetOwner())` runs on the action CDO.

Score formula for an action with N considerations:

```text
ModificationFactor = 1 - 1 / N
For each consideration score S (0..1):
    MakeUp = (1 - S) * ModificationFactor
    Final  = S + MakeUp * S
Score = product of all Final values
```

Special cases in `ScoreAction`:

- A null action scores 0.
- An action with no considerations scores 1.
- A null consideration class is skipped. If the component has no owner, every consideration is skipped and the score is 1.

## Lifetime

- The brain component does not tick. The constructor sets `PrimaryComponentTick.bCanEverTick` to false.
- The component does not override `BeginPlay` or `EndPlay`.
- Actions and considerations are never instanced. The brain uses their CDOs, which live while the class is loaded.
- `BestAction` holds a CDO pointer. `ChooseAction` sets it to null before each choice.
- The consideration constructor adds two keys, (0, 0) and (1, 1), to `ConsiderationCurve.EditorCurveData` if the curve is empty.

## Extension Points

| Point | Kind | Signature |
|---|---|---|
| `UNsSynapseConsideration::CalculateScore` | `BlueprintNativeEvent`, const | `float CalculateScore(AActor* InOwner) const`. The default returns 0. |
| `UNsSynapseAction::ExecuteAction` | `BlueprintNativeEvent` | `void ExecuteAction(AActor* InActor)`. The default does nothing. |
| `UNsSynapseBrainComponent::Think` | Virtual, `BlueprintCallable` | `virtual UNsSynapseAction* Think()` |
| `UNsSynapseBrainComponent::ThinkAndReact` | Virtual, `BlueprintCallable` | `virtual void ThinkAndReact()` |
| Subclass | `Blueprintable` | All three classes accept Blueprint and C++ child classes. |

`ChooseAction` and `ScoreAction` are not virtual. To change the score rule, override `Think` and call your own scoring code.

The plugin has no delegates, interfaces, or settings classes.

## Dependencies

| Dependency | Kind | Why |
|---|---|---|
| `Core` | Public module | Core types. |
| `CoreUObject` | Private module | `UObject` and reflection. |
| `Engine` | Private module | `UActorComponent`, `FRuntimeFloatCurve`, `UKismetMathLibrary`. |
| `Slate` | Private module | Listed in `Build.cs`. The source does not use it. |
| `SlateCore` | Private module | Listed in `Build.cs`. The source does not use it. |

The public headers include `Components/ActorComponent.h` and a curve header from the `Engine` module. `Engine` is a private dependency, so a module that includes these headers must add `Engine` itself. The `.uplugin` lists no plugin dependencies.

## Performance

- One `Think` call runs one `CalculateScore` and one curve evaluation for each consideration of each action.
- The scoring loop makes no allocations.
- The brain does not tick and starts no timers.

## Networking

The plugin does not replicate.
