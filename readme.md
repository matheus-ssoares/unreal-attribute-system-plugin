# Attribute System Plugin

A generic, data-driven attribute system for Unreal Engine 5. This plugin handles stats (Health, Stamina, Mana, etc.), logic processing, and UI binding, entirely decoupled from specific gameplay logic.

## 📦 Features

* **Data-Driven Attributes:** Define stats (Health, Mana, XP) as `Data Assets`.
* **Generic Component:** One component (`AttributeComponent`) handles all stats for any actor.
* **Tag-Based Triggers:** Uses **Gameplay Tags** to broadcast specific events (e.g., `Event.Death`, `State.Exhausted`) when an attribute reaches zero.
* **UI System:** Includes a C++ base widget (`AttributeWidget`) that handles math and event binding, allowing designers to focus purely on visual implementation.

---

## 🚀 Installation

1.  Copy the `AttributeSystem` folder into your project's `Plugins/` directory.
2.  Open your project. Unreal Engine will ask to rebuild the plugin. Click **Yes**.
3.  Ensure the plugin is enabled in **Edit > Plugins**.

### Dependencies
This plugin requires the **GameplayTags** and **UMG** modules. These are enabled by default in the plugin's `.uplugin` file.

---

## 🛠️ Setup Guide

### 1. Define Gameplay Tags
To handle specific events (like Death), you must define Gameplay Tags in your Project Settings.

1.  Go to **Edit > Project Settings > Project > Gameplay Tags**.
2.  Click **Manage Gameplay Tags**.
3.  Add tags for your specific needs, for example:
    * `Event.Death` (For Health)
    * `State.Exhausted` (For Stamina)

### 2. Create Attributes
Attributes are created as **Data Assets** in the Content Browser.

1.  Right-click in the Content Browser.
2.  Select **Miscellaneous > Data Asset**.
3.  Search for and select **`AttributeData`**.
4.  Configure the asset:
    * **Name:** Display name (e.g., "Health").
    * **Default Max Value:** The starting value (e.g., 100).
    * **Zero Trigger Tag:** Select the tag to fire when this reaches 0 (e.g., `Event.Death`).

### 3. Add to Character
1.  Open your Character Blueprint (e.g., `BP_Player`).
2.  Add the **`AttributeComponent`**.
3.  In the Details Panel, find the **Default Attributes** array.
4.  Add your created Data Assets (e.g., `DA_Health`, `DA_Stamina`).

---

## 🎮 Usage (Blueprints)

### Modifying Attributes (Damage / Healing)
To change a value, call `ApplyAttributeChange` on the component.

* **Target:** The `AttributeComponent`.
* **Attribute:** The Data Asset reference (e.g., `DA_Health`).
* **Delta:** The amount to change. Use **negative** numbers for damage.

```blueprint
[AttributeComponent] -> ApplyAttributeChange( Attribute: DA_Health, Delta: -10.0 )