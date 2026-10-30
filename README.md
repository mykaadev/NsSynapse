<!-- GH_ONLY_START -->
<h1 align="center">
  <br>
  <a href="https://github.com/mykaadev/NsSynapse"><img src="https://raw.githubusercontent.com/mykaadev/NsSynapse/refs/heads/main/Resources/Banner.png" alt="NsSynapse" width="400"></a>
</h1>

<h4 align="center">A small Utility AI for Unreal Engine: score each action, then run the best one.</h4>

<div align="center">
    <a href="https://github.com/mykaadev/NsSynapse/commits/main"><img src="https://img.shields.io/github/last-commit/mykaadev/NsSynapse?style=plastic&logo=github&logoColor=white" alt="GitHub Last Commit"></a>
    <a href="https://github.com/mykaadev/NsSynapse/issues"><img src="https://img.shields.io/github/issues-raw/mykaadev/NsSynapse?style=plastic&logo=github&logoColor=white" alt="GitHub Issues"></a>
    <a href="https://github.com/mykaadev/NsSynapse/pulls"><img src="https://img.shields.io/github/issues-pr-raw/mykaadev/NsSynapse?style=plastic&logo=github&logoColor=white" alt="GitHub Pull Requests"></a>
    <a href="https://github.com/mykaadev/NsSynapse"><img src="https://img.shields.io/github/stars/mykaadev/NsSynapse?style=plastic&logo=github" alt="GitHub Stars"></a>
    <a href="https://twitter.com/mykaadev/"><img src="https://img.shields.io/twitter/follow/mykaadev?style=plastic&logo=x" alt="Twitter Follow"></a>

<p style="display:none;">
  <a href="#-summary">👀 Summary</a> •
  <a href="#-features">📦 Features</a> •
  <a href="#-requirements">⚙️ Requirements</a> •
  <a href="#-installation">🛠️ Installation</a> •
  <a href="#-getting-started">🚀 Getting Started</a> •
  <a href="#-how-a-score-is-made">🧮 How a Score Is Made</a> •
  <a href="#-api">🔧 API</a> •
  <a href="#-limits">🚧 Limits</a> •
  <a href="#-documentation">📚 Documentation</a> •
  <a href="#-credits">❤️ Credits</a> •
  <a href="#-support">📞 Support</a> •
  <a href="#-license">📃 License</a>
</p>
<a href="https://buymeacoffee.com/mykaadev"><img src="https://www.svgrepo.com/show/476855/coffee-to-go.svg" alt="Coffee" width="50px"></a>
<p><b>Buy me a coffee!</b></p>
</div>
<!-- GH_ONLY_END -->

## 👀 Summary
NsSynapse is a Utility AI for Unreal Engine. An actor gets a brain component with a list of actions. Each action has considerations, and each consideration gives a score from 0 to 1. The brain multiplies the scores, picks the action with the highest result, and can run it. You make actions and considerations as Blueprint or C++ child classes.

NsSynapse does not find paths, sense the world, or run animations. The brain does not tick, so your game code decides when the agent thinks. It does not replace a Behavior Tree for long, ordered tasks.

## 📦 Features
- **Brain component**: `UNsSynapseBrainComponent` scores its action list and keeps the best action.
- **Actions**: Child classes of `UNsSynapseAction` hold considerations and run `ExecuteAction`.
- **Considerations**: Child classes of `UNsSynapseConsideration` return a raw score from `CalculateScore`.
- **Response curve**: Each consideration maps its raw score through **Consideration Curve**.
- **Score compensation**: A make-up factor stops one low score from removing an action too early.
- **Busy flag**: `ThinkAndReact` does nothing while the brain is busy.
- **Blueprint support**: All main functions are Blueprint callable, and both events are Blueprint overridable.

## ⚙️ Requirements
Unreal Engine 5.7+

The module runs on Win64, Mac, and Linux.

## 🛠️ Installation
1. **Clone** or download this repository.
2. Copy the `NsSynapse` folder into the `Plugins` folder of your project.
3. For C++, add `"NsSynapse"` to the dependencies of your game module in its `Build.cs`.
4. Generate the project files and enable the plugin.

## 🚀 Getting Started
In Blueprint:

1. Make a child Blueprint of `NsSynapseConsideration`. Override `Calculate Score` and return a value from 0 to 1.
2. Make a child Blueprint of `NsSynapseAction`. Override `Execute Action`. Add the consideration to **Considerations**.
3. Add the **Ns Synapse Brain** component to your AI actor.
4. Add the action class to **Possible Actions** on the component.
5. Call `Think And React` on the component when the agent must decide, for example from a timer.

In C++:

```cpp
#include "Classes/NsSynapseBrainComponent.h"
#include "Classes/NsSynapseConsideration.h"

UCLASS()
class ULowHealthConsideration : public UNsSynapseConsideration
{
    GENERATED_BODY()

public:
    virtual float CalculateScore_Implementation(AActor* const InOwner) const override
    {
        const AMyBot* const Bot = Cast<AMyBot>(InOwner);
        return Bot != nullptr ? 1.f - Bot->GetHealthPercent() : 0.f;
    }
};

// In AMyBot: Brain = CreateDefaultSubobject<UNsSynapseBrainComponent>(TEXT("Brain"));
Brain->ThinkAndReact();
```

## 🧮 How a Score Is Made
| Step | Rule |
|---|---|
| Raw score | `CalculateScore` result, clamped to 0..1 |
| Curve | **Consideration Curve** maps the raw score. The brain clamps the result to 0..1. The default curve is a line from (0, 0) to (1, 1) |
| Make-up | With N considerations: `Final = S + (1 - S) * (1 - 1/N) * S` |
| Action score | The product of all `Final` values. An action with no considerations scores 1 |
| Choice | The highest score above 0 wins. On a tie, the first action in the list wins |

## 🔧 API
- `UNsSynapseBrainComponent` – The actor component that scores actions and runs the best one.
- `Think()` – Scores **Possible Actions**, stores the best action, and returns it.
- `ThinkAndReact()` – Calls `Think`, then calls `ExecuteAction` on the best action. Does nothing while busy.
- `ChooseAction(Actions)` – Scores the given action classes and stores the best one.
- `ScoreAction(Action)` – Returns the combined score of one action.
- `GetBestAction()` – Returns the action from the last choice.
- `SetBusy(bool)` / `IsBusy()` – Set and read the busy flag.
- `UNsSynapseAction::ExecuteAction(Actor)` – `BlueprintNativeEvent`. Put the behavior here.
- `UNsSynapseConsideration::CalculateScore(Actor)` – `BlueprintNativeEvent`. Return the raw score.

## 🚧 Limits
- The brain uses the class default object of each action and consideration. All agents share these objects, so they must not hold per-agent data.
- An action with a score of 0 is never chosen. If all actions score 0, the best action is null.
- The plugin does not replicate.
- The plugin has no debug draw, console commands, or log category.

## 📚 Documentation
- [User Guide](https://mykaadev.github.io/plugins/nssynapse/user-guide/) – Setup, common tasks, settings, and debug tools.
- [Technical Documentation](https://mykaadev.github.io/plugins/nssynapse/tech-documentation/) – Architecture, lifetime, extension points, and tests.

<!-- GH_ONLY_START -->
## ❤️ Credits
<a href="https://github.com/mykaadev/NsSynapse/graphs/contributors"><img src="https://contrib.rocks/image?repo=mykaadev/NsSynapse"/></a>

## 📞 Support
Reach out via the **[profile page](https://github.com/mykaadev)**.

## 📃 License
[![License](https://img.shields.io/badge/license-MIT-green)](https://www.tldrlegal.com/license/mit-license)
<!-- GH_ONLY_END -->
