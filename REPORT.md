# Pac-Man Project: Technical Report
**Student:** Niels Hertoghs (s0241591)  
**Course:** Advanced Programming 2025  
**Repository:** https://github.com/Niels-Hertoghs/packman

---

## 1. Introduction

This report presents the design and implementation of an interactive Pac-Man game in C++ using the SFML graphics library. The project demonstrates advanced C++ features, proper software architecture, and the strategic application of design patterns to create a maintainable, extensible codebase with clear separation between game logic and visual representation.

## 2. Architecture Overview

### 2.1 Core Design Philosophy

The architecture is built on three fundamental principles:

1. **Separation of Concerns**: Complete isolation between logic (`code/logic/`) and representation (`code/view/`)
2. **Extensibility**: Modular design allowing easy addition of new entities, behaviors, and game states
3. **Type Safety**: Extensive use of smart pointers, const-correctness, and modern C++ features

### 2.2 Library Structure

The project is organized into two distinct compilation units:

- **Logic Library** (`packman_logic`): A standalone static library containing all game mechanics, entity behaviors, and world management. This library is completely independent of SFML and can be compiled without graphics dependencies, as verified by the CI pipeline.
  
- **View Executable** (`packman`): Links against the logic library and implements all SFML-specific rendering, input handling, and state management.

This separation is enforced through CMake's modular build system, with the logic library having its own `CMakeLists.txt` in `code/logic/`.

### 2.3 Coordinate System Design

A normalized coordinate system ([-1, 1] bounds) is used throughout the logic layer. The `Camera` class transforms these normalized coordinates to pixel values based on window dimensions. This abstraction ensures:
- Resolution independence
- Potential for non-graphical interfaces (e.g., text-based)
- Clean separation between world space and screen space

## 3. Design Pattern Implementation

### 3.1 Model-View-Controller (MVC)

The MVC pattern forms the backbone of the architecture:

- **Model** (`code/logic/entities/`): Entity classes (`Pacman`, `Ghost`, `collectable`, `wall`) contain state and behavior logic
- **View** (`code/view/entities/`): Corresponding view classes (`entityView` hierarchy) handle SFML rendering
- **Controller**: 
  - `world`: Manages entity interactions, collision detection, and game rules
  - `stateManeger`: Controls game state transitions
  - `game`: Processes user input and delegates actions to the world

**Key Design Decision**: Rather than having entities directly render themselves, each model entity can have associated observers (views) that react to state changes. This allows multiple views for the same entity or no view at all for testing.

### 3.2 Observer Pattern (Template-Based)

The Observer pattern is implemented with a modern, type-safe approach:

```cpp
template <typename notification>
class Observer {
public:
    virtual void notify(const notification& message) = 0;
};
```

**Innovation**: The template-based design preserves type information, avoiding dynamic casts and providing compile-time type safety. This is used in two contexts:

1. **Model-View Communication**: Entity views observe their models to react to state changes (position updates, death events, direction changes)
2. **Score System**: The `Score` class observes game events (coin collection, ghost eating, level completion) to calculate scores using the `scoreNotifications` enum

**Rationale**: Templates make the observer pattern more flexible than traditional inheritance-based approaches, allowing different notification types without code duplication.

### 3.3 Abstract Factory Pattern

The `abstractFactory` interface defines creation methods for all game entities:

```cpp
virtual std::shared_ptr<Pacman> createPacman(double x, double y, float speed) = 0;
virtual std::shared_ptr<Ghost> createGhost(ghostTypes type, ...) = 0;
// ... other creation methods
```

The `concreteFactory` (in `code/view/`) implements this interface, creating entities with their corresponding SFML views already attached as observers.

**Design Advantage**: The `world` class in the logic library can create entities without any knowledge of SFML. It simply calls factory methods, and the concrete implementation handles view attachment transparently.

### 3.4 Singleton Pattern

Two utility classes use the Singleton pattern:

1. **`Stopwatch`**: Provides centralized time management using C++'s `<chrono>` library
   - Tracks `deltaTime` for frame-rate independent movement
   - Manages timing for ghost spawning, fear mode duration, and score decay
   - Ensures consistent time source across all game components

2. **`Random`**: Encapsulates a Mersenne Twister pseudo-random number generator
   - Provides high-quality randomness for ghost AI decisions
   - Single seed ensures reproducibility when needed
   - Avoids the pitfalls of legacy `rand()`/`srand()`

**Implementation**: Both use the Meyer's Singleton pattern with smart pointers:

```cpp
static std::shared_ptr<Stopwatch> getInstance() {
    if (!_instance) {
        _instance = std::shared_ptr<Stopwatch>(new Stopwatch());
    }
    return _instance;
}
```

Copy constructors and assignment operators are deleted to enforce single-instance semantics.

### 3.5 State Pattern with Stack-Based FSM

The state machine manages game flow through a stack of states:

- **`menuState`**: Main menu with scoreboard display
- **`LevelState`**: Active gameplay
- **`pauseState`**: Paused game (retains LevelState beneath)
- **`VictoryState`**: Level completion screen
- **`gameOverState`**: Game over screen

**Key Innovation**: Using a stack rather than simple state transitions allows pausing without losing game state. When pausing, `pauseState` is pushed; popping returns to the exact `LevelState` that was running.

**State Transitions**:
- Menu → Level (new game)
- Level → Pause (stack push)
- Pause → Level (stack pop)
- Level → Victory/GameOver (conditional)
- Victory → Next Level (new LevelState)

Each state is responsible for its own transitions, keeping the `stateManeger` agnostic to specific state logic.

## 4. Technical Highlights

### 4.1 Ghost AI Implementation

The AI system demonstrates polymorphism and strategy variation:

- **`Ghost` base class**: Common behavior (collision, fear mode, movement mechanics)
- **`manhattanGhost` subclass**: Implements Manhattan distance pathfinding
  - One ghost: random direction locking (50% probability at intersections)
  - Two ghosts: target position ahead of Pac-Man's direction
  - One ghost: direct pursuit of Pac-Man

**Fear Mode Logic**: In fear mode, ghosts maximize Manhattan distance instead of minimizing it, creating authentic escape behavior. Direction reversal at fear mode start prevents instant recapture.

### 4.2 Dynamic Difficulty Scaling

The `startWorld(int level)` method adjusts:
- Ghost speeds: `baseSpeed * (1 + level * 0.1)`
- Pac-Man speed: slight increase per level
- Fear mode duration: `baseDuration / (1 + level * 0.15)`

This ensures increasing challenge without requiring manual tuning per level.

### 4.3 Score System Design

The scoring mechanism combines multiple factors:

1. **Time-Based Bonuses**: Shorter time between coin collections yields higher multipliers (tracked via `Stopwatch::eatCollectable()`)
2. **Entity Values**: Coins, fruits, and ghosts have base point values
3. **Score Decay**: Score gradually decreases over time (checked via `Stopwatch::decScore()`)
4. **Level Completion Bonuses**: Bonus points for clearing levels

The `Score` class receives events through the observer pattern, keeping scoring logic decoupled from game entities.

### 4.4 Memory Management

**Consistent Use of Smart Pointers**:
- `std::shared_ptr`: For entities with shared ownership (e.g., entities in multiple containers, observer relationships)
- `std::unique_ptr`: For exclusive ownership (e.g., factory ownership by world, state ownership by state manager)
- Raw references: Only for temporary access within function scopes

**Validation**: The project has been verified with Valgrind to ensure no memory leaks.

### 4.5 Continuous Integration

The project uses two CI pipelines:

1. **CircleCI** (`config.yml`): Full build with SFML
2. **GitHub Actions** (`main.yml`): Builds logic library independently, verifying separation

Both must pass for commits to be considered successful, ensuring architectural integrity.

## 5. Key Design Decisions

### 5.1 Template-Based Observer Pattern

Traditional observer patterns use base class pointers, requiring dynamic casts to recover concrete types. The template-based approach:
- Maintains type safety at compile time
- Eliminates runtime overhead of dynamic casts
- Allows different notification types for different observer contexts

### 5.2 Normalized Coordinate System

Using [-1, 1] bounds rather than pixel coordinates:
- Makes game logic resolution-independent
- Simplifies entity positioning (center is [0, 0])
- Enables theoretical alternative renderers (terminal, web canvas)

### 5.3 Namespace Organization

- `logic::` namespace: All game logic (world, entities, utilities)
- `view::` namespace: All SFML rendering and UI components

This reinforces the separation and prevents accidental coupling.

### 5.4 Entity Polymorphism

The entity hierarchy enables:
- Uniform collision detection (all entities have bounding boxes)
- Generic containers (vector of base class pointers)
- Specialized behavior through virtual methods

Example hierarchy:
```
entity
├── wall
├── invisibleWall
├── movableEntity
│   ├── Pacman
│   └── Ghost
│       └── manhattanGhost
└── collectable
    ├── coin
    └── fruit
```

## 6. Challenges and Solutions

### Challenge 1: Observer Lifecycle Management
**Problem**: Views need to observe models, but improper pointer management could cause dangling references.  
**Solution**: Shared pointers for models allow views to safely observe without ownership concerns. Views are typically owned by the same container that owns models.

### Challenge 2: Fear Mode Coordination
**Problem**: All ghosts must transition to fear mode simultaneously when any fruit is eaten.  
**Solution**: The `world::startFearMode()` method iterates through all ghosts and invokes their fear mode transition, centralizing this coordination.

### Challenge 3: Frame-Rate Independence
**Problem**: Game speed shouldn't depend on hardware performance.  
**Solution**: All movement is multiplied by `deltaTime` from the `Stopwatch` singleton. A frame rate cap (optional, 60 FPS) prevents excessive speed on high-performance systems.

### Challenge 4: State Stack Integrity
**Problem**: Transitioning states without losing context (e.g., pausing).  
**Solution**: Stack-based state management where pausing pushes a new state rather than replacing it. Unpausing simply pops the pause state.

## 7. Code Quality Measures

- **Clang-format**: Automatic code formatting with provided configuration
- **Doxygen**: Comprehensive API documentation for all public methods
- **Const-correctness**: Liberal use of `const` for methods and parameters
- **Override keyword**: Explicit marking of virtual method overrides
- **Exception handling**: File I/O wrapped in try-catch blocks
- **Type initialization**: All primitive types explicitly initialized

## 8. Potential Extensions

The current architecture naturally supports several extensions:

1. **Additional Ghost AI**: New ghost subclasses can implement alternative pathfinding (A*, BFS)
2. **Procedural Maps**: Map loading interface could be extended to generate levels algorithmically
3. **Network Multiplayer**: Logic library could be adapted for server-side game state management
4. **Replay System**: Observer pattern could record events for replay functionality
5. **Modding Support**: Factory pattern enables loading custom entity implementations

## 9. Conclusion

This Pac-Man implementation demonstrates that thoughtful architecture pays dividends in maintainability and extensibility. The clear separation between logic and representation, combined with strategic use of design patterns, creates a codebase that is:

- **Testable**: Logic can be tested independently of graphics
- **Portable**: Different platforms or rendering backends could be swapped
- **Extensible**: New entities, behaviors, and states integrate naturally
- **Maintainable**: Clear responsibilities and loose coupling simplify modifications

The project showcases advanced C++ features (templates, smart pointers, chrono) while maintaining readability and adhering to modern best practices. Most importantly, the design patterns are not forced into the code; each serves a genuine architectural need, making the codebase a practical demonstration of software engineering principles in action.

---

**Note**: Full API documentation is available in the `html/` directory (generated by Doxygen), and gameplay demonstration can be found in the linked video in the README.
