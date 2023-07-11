<p align="center">
  <a href="#" rel="noopener" target="_blank"><img width="150" src="/Resources/Icon128.png" alt="CommonVehicle logo"></a>
</p>

<h1 align="center">Common Vehicle [Unreal Engine]</h1>

<div align="center">
  
[![license](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/mrrobinofficial/unreal-commonvehicle/blob/HEAD/LICENSE.txt)
![plugin-status](https://img.shields.io/badge/plugin_status-wip-yellow)
![maintenance-status](https://img.shields.io/badge/maintenance-passively--maintained-yellowgreen.svg)

</div>

#

## ⚙️ Supported Platforms
This plug-in was last built against Unreal Engine **5.2**. It was built with [*Enhanced Input*](https://docs.unrealengine.com/5.2/en-US/enhanced-input-in-unreal-engine/) plugin. However, since version **5.1**, the legacy input system is now being deprecated and will be replaced by the Enhanced Input system.

Chaos Vehicles is Unreal Engine's lightweight system for performing vehicle physics simulations. You can read more about Chaos Vehicles and how to get [*started*](https://docs.unrealengine.com/5.2/en-US/how-to-set-up-vehicles-in-unreal-engine/).

## ⚒️ Installation

You can either install via Epic Games Marketplace.

[*Here*]() is the link.

Or you can install via [*git*](https://git-scm.com/). Here is the command for installing it.

```console
git clone git@github.com:MrRobinOfficial/Unreal-CommonVehicle.git CommonVehicle
```

#

<details open> 
    <summary><h2>🖼️ Screenshots</h2></summary>
</details>

#

## 📝 Quick guide

To get started with this plugin, you can effortlessly extend either the `ACarPawn` or `ACarDriveablePawn` classes. The `ACarDriveablePawn` class provides additional functionality for handling input and camera movement, enhancing the control and immersive experience.

Furthermore, it is recommended to configure the input actions using the Enhanced Input system, which has been officially adopted since Unreal Engine version **5.1**. This system replaces the deprecated input system and offers improved features and flexibility.

Once you have completed the configuration and setup process, your chaos vehicle is ready to go! If you need assistance with setting up animations, engine curves, or physics, we have a helpful video tutorial available for you to [*watch*](https://www.youtube.com/watch?v=tR3sSMD-D0E) by **LeafBranchGames**.

Now that your chaos vehicle is complete, you can further enhance its functionality by tweaking it in the blueprint editor. To explore the wide range of features and possibilities offered by this plugin, we  **recommend** reading the detailed `Overview` section or exploring the comprehensive documentation available in our GitHub repository.

*Unleash the full potential of your chaos vehicle and delve into the extensive functionality provided by this plugin. Enjoy the immersive experience and create captivating projects with ease.*

## 📌 Overview

In this plugin, you have a couple of classes to keep track on.

### `IVehicle`

```cpp
#include "Vehicle.h"
```

*Interface for basic functionally for a vehicle (boat, car, airplane)*

#### Functions
* `void Honk()`
* `void Explode()`

### `UCommonVehicleMovementComponent`

```cpp
#include "Components/CommonVehicleMovementComponent.h"
```

*Extends from `UChaosWheeledVehicleMovementComponent` and contains extra functionality. Such as clutch simulation and more defined getters/setters.*

[Click here](https://docs.unrealengine.com/5.2/en-US/API/Plugins/ChaosVehicles/UChaosWheeledVehicleMovementComp-/) for reading more about `UChaosWheeledVehicleMovementComponent` in the API docs.

Contains extra multicast delegates, such as `OnEngineStateChanged` and `OnGearChanged`.

#### Functions
* `void SetClutchInput()`
* `void IncreaseClutchInput()` and `void DecreaseClutchInput()`
* `float GetForwardSpeedKmh()` and `float GetForwardSpeedMS()`
* `bool GetEngineState()`

#### `UCommonChaosWheeledVehicleSimulation`

*Extends from `UChaosWheeledVehicleSimulation` which handles the vehicle simulation. It overrides the class functionality, to add more functionality, such as clutch simulation and ability to stall the engine.*

[Click here](https://docs.unrealengine.com/5.2/en-US/API/Plugins/ChaosVehicles/UChaosWheeledVehicleSimulation/) for reading more about `UChaosWheeledVehicleSimulation` in the API docs.

### `ACarPawn`

```cpp
#include "Vehicles/CarPawn.h"
```

*Pawn for basic functionally of a car. Such as headlights, taillights and movement component.*

#### Functions
* `void SetLightState()`
* `ELightState GetLightState()`

### `ACarDriveablePawn`

```cpp
#include "Vehicles/CarDriveablePawn.h"
```

*Extends from `ACarPawn` and contains extra functionality for handling player input and camera movement.*

### `UVehicleLibrary`

```cpp
#include "Library/VehicleLibrary.h"
```

*A library containg static functions for `ACarPawn` and `IVehicle`.*

## 🆘 Support
If you have any questions or issue, just write either to my [YouTube channel](https://www.youtube.com/@mrrobinofficial), [Email](mailto:mrrobin123mail@gmail.com) or [Twitter DM](https://twitter.com/MrRobinOfficial).

## 🔗 References
- [Introduction to Unreal Engine Plugins](https://docs.unrealengine.com/5.0/en-US/plugins-in-unreal-engine/)
- [Documentation for Chaos Vehicles in Unreal Engine](https://docs.unrealengine.com/5.2/en-US/vehicles-in-unreal-engine/)
