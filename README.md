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
- **Blueprint-ready components** for actions and considerations.
- **Brain Component** to select and execute the best action.
- **Custom response curves** for considerations.
- **Simple API** that can be extended to fit any project.

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

```cpp
// Example setup in C++
BrainComponent->PossibleActions = { AttackAction, FleeAction };
BrainComponent->Think();
```

## ❤️ Credits
<a href="https://github.com/mykaadev/NsUtilityAI/graphs/contributors"><img src="https://contrib.rocks/image?repo=mykaadev/NsUtilityAI"/></a>

## 📞 Support
Reach out via the **[profile page](https://github.com/mykaadev)**.

## 📃 License
[![License](https://img.shields.io/badge/license-MIT-green)](https://www.tldrlegal.com/license/mit-license)
