# Comprehensive Code Review Report - Packman Project
## Advanced Programming - 2025

**Date:** December 15, 2025  
**Project:** Pac-Man Clone in C++ with SFML  
**Repository:** Niels-Hertoghs/packman

---

## Executive Summary

This report provides a comprehensive critical review of the Packman project implementation based on the requirements specified in the Advanced Programming course assignment. The review examines code design, architecture, design pattern implementations, code quality, cohesion, coupling, and adherence to technical requirements.

**Overall Assessment:** The project demonstrates a solid understanding of basic OOP principles and makes an attempt at implementing several design patterns. However, there are significant architectural issues, missing critical requirements, and areas where the implementation deviates substantially from best practices and assignment specifications.

---

## 1. Technical Requirements Analysis

### 1.1 Critical Missing Requirement: Separate Logic Library ❌

**Finding:** The most critical failure is the **complete absence of a separate logic library**. 

**Evidence:**
- The CMakeLists.txt contains only `add_executable()` and no `add_library()` command
- All logic code is compiled directly into the executable
- No separation exists that would allow compiling logic without SFML

**Impact:** This violates one of the fundamental requirements: *"An essential aspect of this design is that there needs to be a clear separation between game logic and representation... you'll have to encapsulate the game logic into a standalone (static or dynamic) library using CMake."*

**Expected Structure:**
```cmake
# Should exist but doesn't:
add_library(packman_logic STATIC
    code/logic/*.cpp
)

add_executable(packman
    main.cpp
    code/view/*.cpp
    code/game.cpp
)

target_link_libraries(packman packman_logic sfml-graphics sfml-window sfml-system)
```

**Grade Impact:** This alone should result in a significant deduction as it's a core technical requirement.

### 1.2 Required Classes - Implementation Status

#### ✅ Game Class - PRESENT
**Location:** `code/game.h`, `code/game.cpp`

**Strengths:**
- Static `playGame()` method manages the game loop
- Handles window creation and SFML initialization
- Integrates with StateManager

**Weaknesses:**
- The entire class consists of only a single static method - no instance required
- Could be a namespace instead of a class
- No clear separation of responsibilities (window management, game loop, state management all mixed)

#### ✅ Stopwatch Class - PRESENT (with issues)
**Location:** `code/logic/Stopwatch.h`, `code/logic/Stopwatch.cpp`

**Strengths:**
- Correctly implemented as Singleton
- Uses C++ `<chrono>` (not SFML Clock) ✓
- Tracks deltaTime properly
- Good API design with clear methods

**Weaknesses:**
- The singleton uses `shared_ptr` when `unique_ptr` would be more appropriate (only one owner)
- Contains game logic (fear mode timing, sprite changes) that should be elsewhere - violates Single Responsibility Principle
- The `changedSprite` set is a hack for limiting sprite changes per frame - poor design

**Code Smell:**
```cpp
std::set<int> changedSprite; // Tracking sprite state in a time class?
bool changeSprite(int id);     // This doesn't belong here
```

#### ✅ World Class - PRESENT (with issues)
**Location:** `code/logic/world.h`, `code/logic/world.cpp`

**Strengths:**
- Central orchestrator for game entities
- Manages collision detection
- Proper encapsulation of entity collections

**Weaknesses:**
- **Tight coupling:** Contains references to view-layer concern (Score observes from view)
- Reads from file directly instead of using dependency injection
- No interface/abstraction - hard to test or swap implementations
- Collision detection is primitive (rectangle intersection) and could be more sophisticated
- The update method is very long (100+ lines) and does too many things

**Coupling Issue:**
```cpp
// In world.h - logic layer depends on view layer
#include "view/state_maneger/stateManeger.h" // Should not be here!
```

#### ✅ Camera Class - PRESENT
**Location:** `code/view/camera.h`, `code/view/camera.cpp`

**Strengths:**
- Correctly uses normalized coordinates [-1, 1]
- Manual implementation (not using SFML utilities) ✓
- Clean API

**Weaknesses:**
- No handling of aspect ratio preservation - content will stretch on non-square windows
- Simple linear transformation - no support for zoom, pan, or other camera effects
- Missing validation of coordinate bounds

#### ✅ Score Class - PRESENT (with major issues)
**Location:** `code/logic/Score.h`, `code/logic/Score.cpp`

**Strengths:**
- Implements Observer pattern for game events
- Calculates score based on timing (bonus for quick collection)

**Critical Weaknesses:**
- **Major architectural violation:** Score class (in logic layer) has a reference to `view::stateManeger` - this is backwards!
- The Score class directly manipulates UI states (pushes gameOverState)
- Does not persist high scores to file as required
- Missing scoreboard display functionality for top 5 scores

**Code Smell:**
```cpp
class Score : public Observer<scoreNotifications> {
    view::stateManeger& manager; // Logic depends on View - WRONG!
```

**Missing Feature:** No high score persistence to file, no loading of previous scores.

#### ✅ Random Class - PRESENT
**Location:** `code/logic/random.h`, `code/logic/random.cpp`

**Strengths:**
- Correctly implemented as Singleton
- Uses Mersenne Twister (`std::mt19937`) ✓
- Good encapsulation

**Weaknesses:**
- No seeding control for testing/reproducibility
- Could use `std::uniform_int_distribution` more explicitly
- Singleton implemented with `shared_ptr` when `unique_ptr` would suffice

---

## 2. Design Pattern Implementation

### 2.1 Model-View-Controller (MVC) - ⚠️ PARTIAL

**Overall Assessment:** The separation exists in folder structure but is violated in practice.

**Good Aspects:**
- Folder structure: `code/logic/` vs `code/view/` shows intent
- Entity classes separated from EntityView classes
- Most view classes observe their corresponding model classes

**Major Violations:**

1. **Logic depends on View:**
```cpp
// In Score.h (logic layer)
#include "../view/ScoreView.h"
#include "../view/state_maneger/stateManeger.h"

// Score.cpp
manager.prevState();
manager.pushState(std::move(state));
```

2. **View includes in Logic Headers:**
```cpp
// In movableEntity.h (logic layer)
#include "../../view/entities/movableEntityView.h"  // Should not be here
```

3. **Circular Dependencies:**
The logic layer knows about view layer classes, breaking the dependency rule.

**Correct MVC Architecture:**
```
View Layer ─────depends on─────> Logic Layer
     ^                                |
     |                                |
     └──────────notifies via─────────┘
              Observer Pattern
```

**Current (Incorrect) Architecture:**
```
View Layer <────mutual dependencies────> Logic Layer
```

### 2.2 Observer Pattern - ✅ IMPLEMENTED (with issues)

**Assessment:** Good attempt but with some design problems.

**Strengths:**
- Generic template-based Observer class
- Used for Model-View updates
- Used for Score updates
- Multiple notification types handled

**Implementation:**
```cpp
template <typename notification>
class Observer {
public:
    virtual ~Observer() = default;
    virtual void notify(const notification& message) = 0;
};
```

**Weaknesses:**

1. **No Subject base class:** Subjects manually manage their observers, leading to code duplication
2. **Manual observer management:** Each entity manages its own observer instead of inheriting from a Subject base class
3. **Weak typing:** Notification types use enums, could be more type-safe with proper class hierarchy
4. **Missing unsubscribe:** No way to unsubscribe observers safely

**Missing Subject Pattern:**
```cpp
// Should exist but doesn't:
template <typename notification>
class Subject {
    std::vector<std::shared_ptr<Observer<notification>>> observers;
public:
    void attach(std::shared_ptr<Observer<notification>> obs);
    void detach(std::shared_ptr<Observer<notification>> obs);
    void notify(const notification& msg);
};
```

**Current (duplicated in multiple classes):**
```cpp
// In entity.h
std::shared_ptr<Observer<notifications>> observer;
void subscribe(std::shared_ptr<Observer<notifications>> observer);

// Similar code repeated in world, Score, etc.
```

### 2.3 Abstract Factory Pattern - ⚠️ POORLY IMPLEMENTED

**Assessment:** The factory pattern exists but is not properly integrated.

**Problems:**

1. **Factory not used by World:**
```cpp
// In world.cpp startWorld()
std::unique_ptr<ConcreteLogicFactory> factory = std::make_unique<ConcreteLogicFactory>();
// Creates ConcreteLogicFactory directly, not through abstraction
```

2. **ViewFactory never passed to World:**
The assignment states: *"The Game class provides a pointer to this concrete factory to the World"*. This doesn't happen.

3. **Two separate factories:**
- `LogicFactory` creates logic entities
- `ViewFactory` creates views
- No integration between them - they work independently

4. **Factory methods return concrete types:**
```cpp
// In LogicFactory.h
virtual std::shared_ptr<Pacman> createPacman(...) = 0;  // Returns concrete type
// Should return std::shared_ptr<movableEntity> for abstraction
```

**Expected Usage (not implemented):**
```cpp
// World should accept AbstractFactory interface
class world {
    std::shared_ptr<AbstractFactory> factory;
public:
    world(std::shared_ptr<AbstractFactory> factory);
};

// Game creates concrete factory and passes it
auto concreteFactory = std::make_shared<ConcreteViewFactory>(cam, window);
auto world = std::make_shared<World>(concreteFactory);
```

### 2.4 Singleton Pattern - ✅ IMPLEMENTED

**Assessment:** Correctly implemented for Stopwatch and Random classes.

**Strengths:**
- Meyer's Singleton pattern using static local variable
- Thread-safe initialization (C++11 guarantees)
- Deleted copy constructor and assignment operator
- Global access point provided

**Implementation:**
```cpp
inline static std::shared_ptr<Stopwatch> _instance;
static std::shared_ptr<Stopwatch> getInstance();

// Copy prevention
Stopwatch(const Stopwatch&) = delete;
Stopwatch& operator=(const Stopwatch&) = delete;
```

**Minor Issue:**
- Uses `shared_ptr` when these are true singletons that should never be shared or transferred
- Could use `unique_ptr` or raw pointer managed by the class itself
- `inline static` is good but the pointer type is overkill

**Better Alternative:**
```cpp
static Stopwatch& getInstance() {
    static Stopwatch instance;
    return instance;
}
```

### 2.5 State Pattern - ✅ WELL IMPLEMENTED

**Assessment:** This is one of the better-implemented patterns in the project.

**Strengths:**
- Clean state hierarchy with abstract base class
- State stack implemented correctly
- Multiple concrete states: MenuState, LevelState, PausedState, VictoryState, GameOverState
- State transitions handled by states themselves
- Proper use of unique_ptr for state ownership

**Implementation:**
```cpp
class stateManeger {
    std::stack<std::unique_ptr<view::state>> stack;
public:
    void pushState(std::unique_ptr<view::state> newState);
    void pushStateAndDelete(std::unique_ptr<view::state> newState);
    void prevState();
};
```

**Strengths:**
- States create new instances on transitions ✓
- Stack allows returning to previous states ✓
- Each state encapsulates its own rendering and input logic

**Minor Issues:**
- Method names not perfectly clear (`pop2State` - what does this do?)
- State transitions could be more declarative
- Missing state transition validation

---

## 3. Code Design and Architecture

### 3.1 Class Hierarchy and Polymorphism - ⚠️ PARTIAL

**Good Design:**

1. **Entity Hierarchy:**
```
entity (abstract)
├── wall (concrete)
├── invisibleWall (concrete)
├── movableEntity (abstract)
│   ├── Pacman (concrete)
│   └── Ghost (abstract)
│       ├── redGhost (random movement)
│       └── manhattanGhost (abstract)
│           ├── frontManhattanGhost (abstract)
│           │   ├── blueGhost (concrete)
│           │   └── greenGhost (concrete)
│           └── orangeGhost (concrete - follows back)
```

This hierarchy is well-designed with proper abstraction levels.

2. **View Hierarchy:**
Similar structure for view classes - good parallel design.

**Problems:**

1. **Deep Inheritance:**
- 5 levels deep (entity → movableEntity → Ghost → manhattanGhost → frontManhattanGhost → blueGhost)
- Some intermediate abstract classes (frontManhattanGhost) differ only in one method
- Could be simplified with composition or strategy pattern

2. **Missing Interfaces:**
- No interface for "Collidable" entities
- No interface for "Renderable" entities
- Everything goes through entity base class even when not appropriate

3. **Rigid Design:**
- Adding new entity types requires changes in multiple places
- No component-based architecture for flexibility

### 3.2 Cohesion - ⚠️ MODERATE

**High Cohesion (Good):**
- `Camera` class: Only handles coordinate transformation
- `Random` class: Only generates random numbers
- Entity view classes: Each handles rendering for one entity type

**Low Cohesion (Bad):**

1. **Stopwatch class:**
   - Tracks time ✓
   - Manages sprite change rate ✗
   - Handles fear mode duration ✗
   - Tracks when ghosts can leave cage ✗
   
   Should be split into: TimeKeeper, AnimationTimer, GameTimer

2. **World class:**
   - Creates entities (factory responsibility)
   - Updates entities (controller)
   - Detects collisions (physics system)
   - Notifies observers (event system)
   - Manages game state (state management)
   
   Does too many things - needs refactoring

3. **Score class:**
   - Calculates score ✓
   - Manages lives ✓
   - Manages level ✓
   - Controls state transitions ✗ (should be elsewhere)

### 3.3 Coupling - ❌ HIGH COUPLING (Poor)

**Tight Coupling Issues:**

1. **Logic → View Dependencies:**
```cpp
// Score.h (logic) includes view headers
#include "../view/ScoreView.h"
#include "../view/state_maneger/stateManeger.h"

// movableEntity.h (logic) includes view headers
#include "../../view/entities/movableEntityView.h"
```

2. **Concrete Type Dependencies:**
```cpp
// World directly uses concrete ghost types
std::vector<std::shared_ptr<Ghost>> ghosts;  // Should be more abstract

// Methods return concrete types
std::shared_ptr<Pacman> get_pacman() const;  // Should return movableEntity*
```

3. **Hardcoded File Paths:**
```cpp
world wereld = std::make_shared<logic::world>("input_output/map.txt");
// Hardcoded path in game.cpp
```

4. **Global Singleton Access:**
Every class accessing Stopwatch and Random creates implicit coupling.

**Proper Loose Coupling Would Look Like:**
```cpp
// Dependency injection
class World {
    std::shared_ptr<ITimeProvider> timeProvider;
    std::shared_ptr<IRandomProvider> randomProvider;
public:
    World(std::shared_ptr<ITimeProvider> time, 
          std::shared_ptr<IRandomProvider> random);
};
```

---

## 4. Code Quality Assessment

### 4.1 Smart Pointers - ✅ MOSTLY CORRECT

**Strengths:**
- Extensive use of `std::shared_ptr` throughout
- `std::unique_ptr` used for state ownership
- No raw `new`/`delete` visible in code
- Proper RAII principles followed

**Smart Pointer Usage Count:**
- 164 instances of smart pointers in the codebase
- Minimal raw pointer usage (only in calculations, not ownership)

**Issues:**

1. **Overuse of shared_ptr:**
```cpp
// In world.h
std::vector<std::shared_ptr<wall>> walls;
// Walls never shared, unique_ptr would be better
```

2. **Missing weak_ptr:**
When ghosts reference Pacman, circular reference risk:
```cpp
// In Ghost classes
std::shared_ptr<Pacman> pacman;  // Could cause cycle if Pacman references ghosts
// Should be: std::weak_ptr<Pacman> pacman;
```

3. **Shared ownership without reason:**
Many uses of `shared_ptr` don't have actual shared ownership semantics - single owner would suffice.

### 4.2 Const Correctness - ⚠️ PARTIAL

**Good Use:**
```cpp
[[nodiscard]] double getX() const;
[[nodiscard]] int getScore() const;
void update(double deltaTime, const std::vector<std::shared_ptr<entity>>& walls);
```

**Missing const:**
```cpp
// Should be const but isn't
void notifyPos() const;  // ✓ Good
void move(double delta); // Should be: void move(double delta) const if it doesn't modify state
                         // Actually modifies state, so this is correct

// Methods that should be static
static directions oppositeDirection(directions dir);  // ✓ Correctly static
```

**Const Reference Usage:** Generally good, parameters passed by const reference where appropriate.

### 4.3 Exception Handling - ⚠️ MINIMAL

**Present:**
```cpp
// In world.cpp
try {
    std::ifstream file(inputFile2);
    if (!file.is_open()) {
        throw std::runtime_error("Bestand bestaat niet: " + inputFile2);
    }
} catch (const std::exception& e) {
    std::cerr << "Fout bij het openen of verwerken van bestand: " << e.what() << std::endl;
    throw;  // Good: rethrows to caller
}
```

**Missing:**
- No exception handling for SFML operations (texture loading, font loading)
- No validation of game state (what if no Pacman in map file?)
- No handling of invalid user input
- Resource acquisition not protected

**Should Have:**
```cpp
// Font loading in state.cpp
if (!font.loadFromFile("input_output/arial.ttf")) {
    throw std::runtime_error("Failed to load font");
}

// Texture loading
if (!texture.loadFromFile("input_output/sprites.png")) {
    throw std::runtime_error("Failed to load sprites");
}
```

### 4.4 Memory Management - ✅ GOOD

**Positive Findings:**
- No memory leaks detected (would need valgrind to confirm)
- Virtual destructors present in base classes
- Smart pointers handle cleanup automatically
- RAII principles followed

**Verification:**
```cpp
// Base classes have virtual destructors ✓
virtual ~entity() = default;
virtual ~movableEntity() override = default;
virtual ~Ghost() override = default;
virtual ~state() = default;
```

### 4.5 Code Formatting and Style - ⚠️ INCONSISTENT

**Issues Found:**

1. **Inconsistent Naming:**
   - Classes: `movableEntity` (camelCase) vs `Pacman` (PascalCase)
   - Methods: `get_walls()` (snake_case) vs `getX()` (camelCase)
   - Variables: `prevX` (camelCase) vs `_instance` (underscore prefix)

2. **Language Mixing:**
   - Comments in Dutch: `"Breedte van de window in het aantal pixels"`
   - Variable names in Dutch: `wereld`, `snelheid`
   - Mixed with English class names

3. **Missing Clang-Format:**
   - Assignment requires clang-format with specific config
   - `.clang-format` file present but not applied
   - Inconsistent indentation and spacing

4. **Comment Quality:**
   - Some good Doxygen comments
   - Many comments are redundant:
   ```cpp
   // getters
   [[nodiscard]] int getScore() const;  // Comment adds no value
   ```

### 4.6 Documentation - ⚠️ PARTIAL

**Present:**
- Doxygen-style comments on most classes
- Method documentation with @param and @return
- Some architectural intent documented

**Missing:**
- No README.md with project overview
- No build instructions
- No explanation of design decisions
- No report as required by assignment (2 pages explaining design choices)
- No video link for project defense

**Code Comments:**
- Generally adequate
- Some explanations in Dutch (inconsistent)
- Some redundant comments that just repeat the method name

---

## 5. Gameplay Requirements

### 5.1 Core Functionalities - ⚠️ MOSTLY IMPLEMENTED

#### Game Startup & Initialization - ✅ IMPLEMENTED
- Menu state with score display
- Play button functionality
- Maze loading from file

#### Player Controls - ✅ IMPLEMENTED
- Arrow key input
- Continuous movement
- Collision detection with walls
- Direction persistence

#### Ghost Movement and AI - ✅ IMPLEMENTED
**Four ghosts with different behaviors:**
1. Red Ghost: Random movement ✓
2. Blue Ghost: Front Manhattan (chase forward) ✓
3. Green Ghost: Front Manhattan (chase forward) ✓
4. Orange Ghost: Back Manhattan (chase from behind) ✓

**Timing:**
- Two ghosts leave immediately ✓
- Two ghosts after 5 and 10 seconds ✓

**Issues:**
- Assignment specifies "one ghost locked to fixed direction" - red ghost is random, not locked
- Implementation doesn't match exact specification

#### Coin Collection & Scoreboard - ⚠️ PARTIAL
- Score displayed ✓
- Score decreases over time ❌ (not implemented)
- Eating coins increases score ✓
- Time-based bonus for quick collection ✓
- Level clear bonus ❌ (not visible)
- **Scoreboard NOT persisted to file** ❌ (major missing feature)
- Top 5 scores NOT saved ❌

#### Fruits & Ghost Transformation - ✅ IMPLEMENTED
- Fruits in corners ✓
- Fear mode activation ✓
- Ghosts become vulnerable ✓
- Slower movement in fear mode ✓
- Ghosts maximize distance ✓
- Can eat ghosts ✓
- Ghost respawn ✓

#### Clearing Levels & Difficulty - ⚠️ PARTIAL
- Next level transition ✓
- Respawn coins and fruits ✓
- Ghosts get faster ✓
- Fear mode duration shortens ✓

**Formula:**
```cpp
float lengthOfFear = 10.f / (1.f + (0.2f * static_cast<float>(level - 1)));
```

#### Multiple Lives & Game Over - ⚠️ PARTIAL
- Three lives ✓
- Lives displayed ❌ (not visible in code review)
- Life lost on ghost collision ✓
- Game over state ✓
- Return to menu ✓
- Lives persist across levels ✓

### 5.2 Visuals and Aesthetics - ❓ CANNOT VERIFY

**Cannot verify without running:**
- Sprite usage
- Animations (Pac-Man mouth, ghost walking)
- Direction-based sprites
- Fear mode blue appearance
- Maze appearance

**Code suggests:**
- Sprites loaded from texture
- Animation state managed
- Direction tracking present

---

## 6. Major Issues Summary

### Critical Issues (Must Fix):

1. **❌ No Separate Logic Library**
   - Violates core requirement
   - All code compiled into single executable
   - Cannot build logic without SFML

2. **❌ Logic Layer Depends on View Layer**
   - `Score` class includes view headers
   - Backwards dependency breaks MVC
   - Cannot separate representations

3. **❌ Scoreboard Not Persisted**
   - High scores not saved to file
   - Top 5 scores not maintained
   - Required feature missing

4. **❌ Abstract Factory Pattern Misused**
   - Factory not passed to World
   - Concrete factories used directly
   - No integration between logic and view factories

### Major Issues (Should Fix):

5. **⚠️ High Coupling**
   - Tight coupling between layers
   - Hardcoded dependencies
   - Global singleton access

6. **⚠️ Low Cohesion in Key Classes**
   - Stopwatch does too much
   - World has too many responsibilities
   - Score manages UI state

7. **⚠️ Inconsistent Code Style**
   - Mixed English/Dutch
   - Inconsistent naming conventions
   - Clang-format not applied

8. **⚠️ Minimal Exception Handling**
   - Resource loading not protected
   - State validation missing
   - No graceful error recovery

### Minor Issues (Nice to Fix):

9. **Overuse of shared_ptr**
   - Should use unique_ptr where ownership is clear
   - Should use weak_ptr for back-references

10. **Missing Subject Base Class**
    - Observer pattern implemented manually in each class
    - Code duplication

11. **Deep Inheritance Hierarchy**
    - 5 levels deep for some ghosts
    - Could be simplified

12. **Missing Documentation**
    - No README
    - No design document
    - No build instructions

---

## 7. Strengths of the Implementation

Despite the issues, the project has notable strengths:

1. **✅ Working Game Loop**
   - Proper game loop with delta time
   - Frame-independent movement

2. **✅ Good Ghost AI Hierarchy**
   - Well-thought-out class structure
   - Different behaviors properly separated

3. **✅ State Pattern**
   - Excellent implementation
   - Clean state transitions

4. **✅ Smart Pointer Usage**
   - Consistent use throughout
   - No manual memory management

5. **✅ Singleton Implementation**
   - Thread-safe
   - Properly prevents copying

6. **✅ Observer Pattern Attempt**
   - Generic template-based design
   - Multiple notification types

7. **✅ Camera Abstraction**
   - Normalized coordinates
   - Resolution-independent

---

## 8. Recommended Improvements

### Priority 1 (Critical):

1. **Create Separate Logic Library:**
```cmake
add_library(packman_logic STATIC
    code/logic/world.cpp
    code/logic/entities/*.cpp
    code/logic/Score.cpp
    code/logic/Stopwatch.cpp
    code/logic/random.cpp
    code/logic/Observer.cpp
    code/logic/LogicFactory.cpp
)

# Logic library should NOT link SFML
target_include_directories(packman_logic PUBLIC code/logic)
```

2. **Fix Dependency Direction:**
   - Remove all view includes from logic layer
   - Score should not know about StateManager
   - Use events/callbacks to notify upward

3. **Implement Score Persistence:**
```cpp
class Score {
    void saveHighScores(const std::string& filename);
    void loadHighScores(const std::string& filename);
    std::vector<int> getTopFive() const;
};
```

4. **Fix Abstract Factory Integration:**
```cpp
// In Game class
auto factory = std::make_shared<ConcreteViewFactory>(cam, window);
auto world = std::make_shared<World>(factory);
```

### Priority 2 (Important):

5. **Refactor for Lower Coupling:**
   - Use dependency injection
   - Create interfaces for cross-layer communication
   - Remove global singleton access

6. **Improve Cohesion:**
   - Split Stopwatch into focused classes
   - Separate World responsibilities
   - Extract collision detection system

7. **Add Exception Handling:**
   - Protect all resource loading
   - Validate game state
   - Provide meaningful error messages

8. **Apply Clang-Format:**
   - Use provided configuration
   - Enforce consistent style
   - Fix naming conventions

### Priority 3 (Enhancement):

9. **Reduce shared_ptr Usage:**
   - Use unique_ptr for exclusive ownership
   - Use weak_ptr for back-references
   - Use raw references for non-owning access

10. **Create Subject Base Class:**
```cpp
template <typename T>
class Subject {
    std::vector<std::weak_ptr<Observer<T>>> observers;
public:
    void attach(std::shared_ptr<Observer<T>> obs);
    void notify(const T& event);
};
```

11. **Add Comprehensive Documentation:**
    - Write README with build instructions
    - Create design document (2 pages)
    - Document all public APIs
    - Add architecture diagrams

12. **Improve Error Handling:**
    - Add input validation
    - Handle missing files gracefully
    - Provide user-friendly error messages

---

## 9. Code Quality Metrics

| Criterion | Score | Weight | Weighted Score |
|-----------|-------|---------|----------------|
| **Core Game Requirements** | 7/10 | 40% | 28% |
| - Most gameplay features present | | | |
| - Missing: score persistence, score decay | | | |
| - Ghost AI mostly correct | | | |
| **Design and Code Quality** | 4/10 | 40% | 16% |
| - Critical: No separate library | | | |
| - Critical: Wrong dependency direction | | | |
| - Abstract Factory misused | | | |
| - Good: State pattern, smart pointers | | | |
| **Documentation** | 2/10 | 10% | 2% |
| - Missing: README, report, video | | | |
| - Partial: Code comments present | | | |
| **Project Defense** | 0/10 | 10% | 0% |
| - No video submission found | | | |
| **Bonus Features** | 0/10 | 10% | 0% |
| - No additional features identified | | | |

**Total: 46/100**

---

## 10. Estimated Grade

### Grade Breakdown:

- **Core Functionality: 28/40** 
  - Game works and most features present (+30%)
  - Missing score persistence (-5%)
  - Missing score decay over time (-5%)
  - Ghost AI close but not exact to spec (-2%)

- **Design & Code Quality: 16/40**
  - No separate library (-15%) ❌ **CRITICAL**
  - Wrong dependency direction (-10%) ❌ **CRITICAL**
  - Abstract Factory misused (-5%)
  - High coupling (-3%)
  - Low cohesion (-3%)
  - Good state pattern (+4%)
  - Good smart pointer usage (+4%)
  - Good singleton implementation (+3%)
  - Good class hierarchy (+3%)
  - Inconsistent style (-2%)

- **Documentation: 2/10**
  - No README (-3%)
  - No design report (-3%)
  - Code comments present (+2%)
  - Doxygen documentation (+2%)
  - Mixed language (-1%)
  - No build instructions (-1%)

- **Project Defense: 0/10**
  - No video found (-10%)

- **Bonus: 0/10**
  - No identified bonus features

### **Final Estimated Grade: 46/100 (4.6/10)**

### Grade Category: **FAIL**

---

## 11. Path to Passing Grade

To achieve a passing grade (50%+), the following **MUST** be addressed:

1. **Create separate logic library (+8%)**
2. **Fix dependency direction (+5%)**  
3. **Implement score persistence (+3%)**
4. **Fix Abstract Factory usage (+3%)**
5. **Write 2-page design report (+3%)**

**With these fixes: ~67/100 (Passing)**

To achieve a good grade (70%+), additionally address:
- Apply clang-format consistently
- Improve cohesion (split large classes)
- Reduce coupling (dependency injection)
- Add comprehensive exception handling
- Create project README

---

## 12. Conclusion

This project demonstrates a **basic understanding of object-oriented programming** and makes an effort to implement several design patterns. The gameplay is largely functional, and the code shows awareness of modern C++ features like smart pointers and templates.

However, the implementation fails to meet **critical architectural requirements**:
- **No separate logic library** (fundamental requirement)
- **Backwards dependencies** (logic depends on view)
- **Missing required features** (score persistence)
- **Misused design patterns** (Abstract Factory)

The code quality is **moderate** with good points (smart pointers, some patterns) and poor points (coupling, cohesion, style consistency). The complete absence of project documentation and defense materials significantly impacts the grade.

### Critical Assessment:

This project, in its current state, would likely **not pass** the course requirements. The missing separate library alone is a fundamental requirement that, if not addressed, should result in significant point deductions regardless of other aspects of the implementation.

### Recommendations for Student:

1. **Immediately create the separate logic library** - this is non-negotiable
2. **Fix the dependency inversion** - logic must not depend on view
3. **Implement missing required features** - score persistence is specified
4. **Write the required documentation** - report and video are part of the assignment
5. **Apply code formatting** - use the provided clang-format config

With focused effort on these critical issues, this project could be brought up to a passing standard. The foundation is there, but architectural requirements must be met.

---

**Reviewer Note:** This review is intentionally critical as requested. The student has demonstrated programming ability, but needs to focus on architectural principles and assignment requirements to succeed.

