# Smells Like Rubber

Smells Like Rubber is an early-stage arcade driving game and engine prototype
written in modern C++. The project currently focuses on responsive
keyboard-driven vehicle movement, a mouse-controlled chase camera, a small
debug driving course, and the engine systems needed to turn those pieces into a
larger game.

The game is built on [SlateEngine](https://github.com/raphaelhounsiagaman/SlateEngine),
which lives in this repository as a Git submodule.

## Current state

- Arcade car controller with acceleration, braking, reverse, drag, steering,
  speed, and heading
- Chase camera with right-mouse orbit and wheel zoom
- Main menu with a queued transition into the game layer
- Canvas UI with labels, buttons, images, text, and mouse interaction
- Independently scheduled update and render stages, both uncapped by default
- Engine-measured updates-per-second and frames-per-second HUD
- Keyboard, mouse, focus, and resize events
- Resizable game window and renderer resources
- Consistent SI gameplay units

This is a prototype rather than a finished game. The road, car, and markings
use simple box geometry so development can stay focused on mechanics and engine
architecture.

## Controls

| Action | Input |
| --- | --- |
| Accelerate | `W` or Up Arrow |
| Brake / reverse | `S` or Down Arrow |
| Steer left | `A` or Left Arrow |
| Steer right | `D` or Right Arrow |
| Orbit camera | Hold Right Mouse Button and move the mouse |
| Zoom camera | Mouse Wheel |
| Start the game | Click **Start Driving** |

## Requirements

- Windows 10 or newer
- Visual Studio 2026 with the Desktop development with C++ workload
- A recent Windows SDK
- Git with submodule support

Premake and SlateEngine are included through the repository and its submodules;
there are no graphics-library packages to install separately.

## Getting started

Clone the repository and its submodules:

```powershell
git clone --recursive https://github.com/raphaelhounsiagaman/SmellsLikeRubber.git
cd SmellsLikeRubber
```

If the repository was cloned without `--recursive`, initialize the submodules:

```powershell
git submodule update --init --recursive
```

Generate the Visual Studio workspace:

```powershell
.\scripts\Setup.bat
```

Open `SmellsLikeRubber.slnx`, choose a configuration, and build the
`SmellsLikeRubber` project. The executable is written to:

```text
bin/<Configuration>/SmellsLikeRubber.exe
```

### Build configurations

| Configuration | Purpose |
| --- | --- |
| `Debug` | Debug symbols and SlateEngine diagnostics |
| `Release` | Optimized development build |
| `Dist` | Fully optimized distribution build |

Generated Visual Studio files and build output are ignored by Git.

## Units and timing

Gameplay code follows a single convention:

- `1` world unit = `1 metre`
- Time values are seconds
- Speed values are metres per second
- Acceleration values are metres per second squared
- Angles are radians
- UI layout and mouse coordinates are screen pixels

Unit-bearing variables and settings include the unit in their names. This keeps
tuning values readable without identity conversion helpers or hidden scale
factors.

The top-right HUD reports completed update cycles as `UPS` and completed
presentations as `FPS`. SlateEngine measures both stages against wall-clock
time rather than estimating one value from the other.

Updates and rendering are uncapped by default. On supported Windows systems,
SlateEngine enables DXGI tearing for immediate presentation; unsupported
systems fall back safely to standard presentation. VSync remains available
through `Renderer::SetVSyncEnabled(true)`.

`ApplicationLoopSettings` can independently limit either stage when a project
needs a specific simulation or rendering rate. A limit of zero means uncapped.

## Architecture

```text
SmellsLikeRubber/
├── Game/
│   ├── Build-SmellsLikeRubber.lua
│   └── src/
│       ├── Gameplay/   Car and chase-camera controllers
│       ├── Meshes/     Reusable primitive mesh creation
│       ├── World/      Debug course construction and rendering
│       ├── GameLayer.* Gameplay orchestration and HUD
│       ├── MainMenuLayer.* Menu UI and queued game transition
│       └── main.cpp    Application composition
├── scripts/            Workspace-generation helper
├── vendor/
│   ├── Premake/        Included project generator
│   └── SlateEngine/    Engine Git submodule
└── premake5.lua        Workspace definition
```

Game code depends only on SlateEngine's public API. The game Premake target
links `SlateEngine` and contains no Direct3D, Direct2D, DXGI, DirectWrite, or
WIC dependencies. SlateEngine's current Windows renderer owns those details
inside its D3D11 backend, leaving the game project ready for future platform
backends.

Layer replacement is deferred until the current update and render pass has
finished. A menu button can therefore request `TransitionTo<GameLayer>()`
without destroying a layer while it is still handling an event or being
iterated.

## Gameplay tuning

Vehicle behavior is configured through `ArcadeCarSettings`, including:

- Forward and reverse speed limits
- Forward and reverse acceleration
- Braking deceleration
- Coasting drag
- Maximum steering rate

Camera behavior is configured independently through `ChaseCameraSettings`.
Keeping controllers separate from rendering and layer orchestration makes
future input sources, vehicles, cameras, and tests easier to add.

## Development direction

Useful next milestones include:

1. Asset management and reusable scene resources
2. Collision queries and lightweight vehicle/world physics
3. A fixed-step gameplay simulation separated from rendering
4. Track data, checkpoints, lap timing, and a restart flow
5. Audio, vehicle visuals, and production game UI
6. Additional SlateEngine platform and rendering backends

## License

This repository does not currently include a license file. Unless a license is
added, all rights remain with the repository owner.
