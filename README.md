<h1 align="center">
  <br>
  <a href="https://github.com/mykaadev/NsUtilityAI/releases"><img src="https://raw.githubusercontent.com/mykaadev/NsUtilityAI/refs/heads/main/Resources/UtilityAIBanner.png" alt="NsUtilityAILogo" width="350"></a>
</h1>

<h4 align="center">A Utility AI framework for Unreal Engine.</h4>

<div align="center">
    <a href="https://github.com/mykaadev/NsUtilityAI/commits/main"><img src="https://img.shields.io/github/last-commit/mykaadev/NsUtilityAI?style=plastic&logo=github&logoColor=white" alt="GitHub Last Commit"></a>
    <a href="https://github.com/mykaadev/NsUtilityAI/issues"><img src="https://img.shields.io/github/issues-raw/mykaadev/NsUtilityAI?style=plastic&logo=github&logoColor=white" alt="GitHub Issues"></a>
    <a href="https://github.com/mykaadev/NsUtilityAI/pulls"><img src="https://img.shields.io/github/issues-pr-raw/mykaadev/NsUtilityAI?style=plastic&logo=github&logoColor=white" alt="GitHub Pull Requests"></a>
    <a href="https://github.com/mykaadev/NsUtilityAI"><img src="https://img.shields.io/github/stars/mykaadev/NsUtilityAI?style=plastic&logo=github" alt="GitHub Stars"></a>
 <a href="https://twitter.com/mykaadev/"><img src="https://img.shields.io/twitter/follow/mykaadev?style=plastic&logo=x" alt="Twitter Follow"></a>

<p style="display:none;">
  <a href="#-summary">👀 Summary</a> •
  <a href="#-what-is-utility-ai">❓ What is Utility AI</a> •
  <a href="#-features">📦 Features</a> •
  <a href="#-requirements">⚙️ Requirements</a> •
  <a href="#-installation">🛠️ Installation</a> •
  <a href="#-api">🔧 API</a> •
  <a href="#-credits">❤️ Credits</a> •
  <a href="#-support">📞 Support</a> •
  <a href="#-license">📃 License</a>
</p>
<a href="https://buymeacoffee.com/mykaadev"><img src="https://www.svgrepo.com/show/476855/coffee-to-go.svg" alt="Coffee" width=50px"></a>
<p><b>Buy me a coffee!</b></p>
</div>

## 👀 Summary
A decision-making framework for Unreal Engine agents where every possible action is evaluated by a set of considerations. The resulting utility score selects which action to execute.

## ❓ What is Utility AI?
Utility AI evaluates many potential actions and ranks them based on their desirability. Each action gathers scores from considerations (for example health, distance or ammo) and the highest score wins. This approach results in more nuanced behaviour than simple state machines or behaviour trees.

### When to use it
- When your agent needs to consider multiple factors for decision making.
- When you want dynamic behaviour without lengthy condition chains.
- When prototyping quick AI logic in Blueprints.

### Why is it good?
- Scales easily as you add more considerations.
- Designers can tweak curves to influence behaviour without coding.
- Works entirely in C++ and Blueprints for flexibility.

## 📦 Features
- **Designer-Friendly**: Tune weights and response curves directly in the Unreal Editor.
- **Modular Architecture**: Extendable C++ base classes for custom actions and considerations.
- **Simple API** that can be extended to fit any project.
- **Blueprint-ready components** for actions and considerations.
- **Brain Component** to select and execute the best action.
- **Custom response curves** for considerations.

## ⚙️ Requirements
Unreal Engine 5.2+

## 🛠️ Installation
1. **[Download](https://github.com/mykaadev/NsUtilityAI/releases)** the latest release.
2. Extract the archive into your project's `Plugins` folder: `.../UEGame/Plugins/NsUtilityAI`.
3. Add the plugin to your `UEGame.uproject` and generate project files.
4. Open the project and enable **NsUtilityAI** if prompted.

## 🔧 Usage / API Reference
### Key Classes
- `UNsUtilAIBrainComponent` – attach to an actor and call **Think** to evaluate actions.
- `UNsUtilAIAction` – base class for actions. Override **ExecuteAction** and provide **Considerations**.
- `UNsUtilAIConsideration` – base class for scoring logic with a customizable curve.

### Main Functions
- `Think()` – evaluates `PossibleActions`, runs the best scoring action.
- `ChooseAction` – given an array of actions, selects the highest scoring one.
- `ScoreAction` – multiplies consideration scores to produce an action utility value.
- `ExecuteAction` – override in your action subclass to perform behaviour.
- `CalculateScore` – override in a consideration to return a raw 0‑1 score.
- `GetBestAction` – returns the action chosen by the last call to **Think**.

### Getting Started
1. In your AI actor, add **`UNsUtilAIBrainComponent`**.
2. Create custom **`UNsUtilAIAction`** subclasses and assign them to the Brain Component’s **`PossibleActions`** array.
3. Implement **`CalculateScore()`** in each **`UNsUtilAIConsideration`** to read your game data.
4. For each Consideration, adjust the **Response Curve** to shape decision sensitivity and assign it to the action that you want..
5. Call **`Think()`** whenever the AI should evaluate and execute an action.

### Shooter Enemy Example

An enemy might provide actions like:

* **Attack Player**
* **Reload Weapon**
* **Find Cover**
* **Retreat**

Each action is scored by its considerations:

| Action | Considerations |
| --- | --- |
| Attack Player | Player in sight, Ammo amount, Health percentage |
| Reload Weapon | Ammo amount, Safe to reload |
| Find Cover | Nearby cover points, Under fire |
| Retreat | Health critically low, No cover available |

### C++ Example

```cpp
// Actor with brain component
AMyBot::AMyBot()
{
    Brain = CreateDefaultSubobject<UNsUtilAIBrainComponent>(TEXT("Brain"));
}

void AMyBot::BeginPlay()
{
    if (Brain != nullptr)
    {
        Brain->Think(); // Chose the best action and execute it
    }
}

// Custom consideration
UCLASS()
class UHealthConsideration : public UNsUtilAIConsideration
{
    GENERATED_BODY()

public:
    virtual float CalculateScore_Implementation(AActor* InOwner) const override
    {
        if (const AMyBot* const Bot = Cast<AMyBot>(InOwner))
        {
            const float HealthScore = Bot->GetCurrentHealth() / Bot->GetMaxtHealth(); 
            return HealthScore;
        }
    }
};

// Custom action
UCLASS()
class UAttackAction : public UNsUtilAIAction
{
    GENERATED_BODY()

    virtual void ExecuteAction_Implementation(AActor* InActor) override
    {
        UE_LOG(LogTemp, Log, TEXT("Firing at player"));
    }
};
```

## ❤️ Credits
<a href="https://github.com/mykaadev/NsUtilityAI/graphs/contributors"><img src="https://contrib.rocks/image?repo=mykaadev/NsUtilityAI"/></a>

## 📞 Support
Reach out via the **[profile page](https://github.com/mykaadev)**.

## 📃 License
[![License](https://img.shields.io/badge/license-MIT-green)](https://www.tldrlegal.com/license/mit-license)
