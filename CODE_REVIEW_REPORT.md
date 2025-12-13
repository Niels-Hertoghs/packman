# Pac-Man Project Code Review Report

## Executive Summary

This report provides a comprehensive review of the Pac-Man game implementation in C++ using SFML, evaluating adherence to design principles, implementation of required design patterns, code quality, and fulfillment of core requirements. The review is structured according to the project specification criteria.

---

## 1. Core Game Requirements (40%)

### 1.1 Game Startup & Initialization
**Status: INCOMPLETE**
- ❌ **Missing Main Menu with Scoreboard**: No menu state shows top 5 scores at startup
- ❌ **No Score Persistence**: No file I/O implementation to save/load high scores
- ✅ Menu state exists but lacks scoreboard display
- ✅ Level state transitions work properly

**Issues:**
1. The `Score` class doesn't implement file I/O for persistent score tracking
2. Menu state (`menuState`) doesn't display any scoreboard
3. No highscore.txt or similar file for storing scores

### 1.2 Player Controls & Interactions
**Status: PARTIAL**
- ✅ Movement controls implemented via `updatePacmanDir()` in world
- ✅ Continuous movement (not discrete)
- ✅ Collision detection with walls
- ✅ Pac-Man continues in last direction until new input or collision
- ✅ Coin collection logic present in world update

### 1.3 Ghost Movement and AI
**Status: GOOD**
- ✅ Four ghost types implemented (red, blue, green, orange)
- ✅ Timed spawn delays (5 and 10 seconds) via `canStartAfter5Sec()` and `canStartAfter10Sec()`
- ✅ Random ghost (redGhost) - probability-based direction choice at intersections
- ✅ Two Manhattan distance ghosts targeting Pac-Man's front (blue, green)
- ✅ One ghost targeting Pac-Man directly (orange)
- ✅ Fear mode and chase mode implementations
- ⚠️ Ghost AI complexity meets requirements but could be clearer

**Observations:**
- Ghost hierarchy is well-structured: `Ghost` → `manhattanGhost` → specific implementations
- AI logic in `chooseAtIntersection()` and `nextDirection()` methods

### 1.4 Coin Collection and Scoreboard
**Status: PARTIAL**
- ✅ Score increases when coins eaten
- ✅ Time-based scoring multiplier implemented (faster collection = more points)
- ✅ Score calculation: `points/lastEatenTime` in `Score::coinEaten()`
- ✅ Level progression when all collectables eaten
- ✅ Bonus points for ghosts and fruits
- ❌ **No persistent scoreboard** - scores not saved to file
- ❌ **Top 5 scores not displayed** at game launch

### 1.5 Fruits and Ghost Transformation
**Status: GOOD**
- ✅ Fruits placed in corners (from map file)
- ✅ Fear mode triggered when fruit eaten
- ✅ Ghosts become slower and reverse direction in fear mode
- ✅ Ghosts try to maximize Manhattan distance in fear mode
- ✅ Eaten ghosts respawn in center
- ✅ Time-limited fear mode via `isFearDone(level)`
- ✅ Fear duration decreases with level: `10 / (1 + 0.2*(level-1))`

### 1.6 Clearing Levels and Scaling Difficulty
**Status: EXCELLENT**
- ✅ Level transition when all collectables eaten
- ✅ Coins and fruits respawn
- ✅ Ghosts return to center
- ✅ Speed scaling: Ghost speed = `0.75 + (level * 0.25)`
- ✅ Pac-Man speed = `1.0 + (level * 0.25)`
- ✅ Fear mode duration decreases with level
- ✅ Points per collectable increase with level

### 1.7 Multiple Lives and Game Over
**Status: GOOD**
- ✅ Three lives (starts with 2 in code, plus initial = 3 total)
- ✅ Lives displayed on screen
- ✅ Ghost collision triggers life loss
- ✅ Entities reset to spawn positions on death
- ✅ Collected items remain collected
- ✅ Lives persist across levels
- ✅ Game over screen transitions to menu

**Score: 28/40**

**Critical Missing Features:**
- No persistent high score storage (file I/O)
- No scoreboard display at startup

---

## 2. Design and Code Quality (40%)

### 2.1 Design Patterns Implementation

#### 2.1.1 Model-View-Controller (MVC)
**Status: PARTIALLY IMPLEMENTED**

**Strengths:**
- ✅ Clear separation between logic (`logic` namespace) and view (`view` namespace)
- ✅ Entity models in `logic/entities/` separate from views in `view/entities/`
- ✅ World acts as controller managing entity interactions

**Critical Flaws:**
- ❌ **MVC VIOLATION**: Logic models hold direct references to view observers
  - `movableEntity` contains `std::shared_ptr<view::movableEntityView> observer`
  - `collectable` contains `std::shared_ptr<view::collectableView> collectableObserver`
  - This creates tight coupling between model and view layers
  
- ❌ **MVC VIOLATION**: Score (model) holds reference to ScoreView
  - `std::shared_ptr<view::ScoreView> scoreObserver` in Score class
  
- ❌ **Dependency Direction Wrong**: Model should NOT know about View
  - Models should only notify via abstract interfaces
  - Views should hold weak references to models

**Proper MVC would require:**
```cpp
// Model (logic) should only know about abstract observers
class movableEntity {
    std::vector<std::weak_ptr<IObserver>> observers;
};

// View holds reference to model
class movableEntityView {
    std::weak_ptr<logic::movableEntity> model;
};
```

**Impact:** This design makes it impossible to use the logic library without SFML, defeating the stated architectural goal.

#### 2.1.2 Observer Pattern
**Status: INCORRECTLY IMPLEMENTED**

**Issues:**
1. **Backwards Observer Pattern**: 
   - Subject (model) holds strong references to observers (views)
   - Should be: Observer holds weak reference to subject
   - Current: `movableEntity.observer` → view
   - Correct: `movableEntityView.model` → entity

2. **Incomplete Abstraction**:
   - `IObserver` interface exists but is underutilized
   - Model classes reference concrete view types instead of abstract observers
   - `view::Observer` requires SFML types (RenderWindow), violating logic/view separation

3. **Notification System**:
   - ✅ `notifications` enum for different events
   - ✅ `notify()` methods implemented
   - ❌ Subject doesn't maintain observer list properly
   - ❌ Single observer per model (not a collection)

**Correct Implementation Would Be:**
```cpp
class Subject {
    std::vector<std::weak_ptr<IObserver>> observers;
    void attach(std::weak_ptr<IObserver> obs);
    void notifyAll(notification msg);
};
```

#### 2.1.3 Abstract Factory Pattern
**Status: NOT IMPLEMENTED**

**Critical Missing Element:**
- ❌ **No Factory Pattern Found**: No AbstractFactory interface
- ❌ **No ConcreteFactory Implementation**: Entities created directly in code
- ❌ **Direct Construction**: World creates entities with `std::make_shared<>`
- ❌ Factory was mentioned in requirements but completely absent

**Impact:** 
- Direct coupling between world logic and SFML view creation
- Impossible to switch graphics libraries without modifying logic code
- Violates stated goal of library separation

**Required Implementation:**
```cpp
// In logic library
class AbstractFactory {
    virtual std::shared_ptr<entity> createWall(...) = 0;
    virtual std::shared_ptr<movableEntity> createPacman(...) = 0;
};

// In view/representation
class ConcreteFactory : public AbstractFactory {
    // Creates entities with views attached
};
```

#### 2.1.4 Singleton Pattern
**Status: CORRECTLY IMPLEMENTED**

**Strengths:**
- ✅ `Stopwatch` implemented as singleton
- ✅ `Random` implemented as singleton
- ✅ Private constructor
- ✅ `getInstance()` static method
- ✅ Deleted copy constructor and assignment operator
- ✅ Thread-safe initialization (C++11 guarantees)
- ✅ Smart pointer usage: `std::shared_ptr`

**Implementation:**
```cpp
inline static std::shared_ptr<Stopwatch> _instance;
static std::shared_ptr<Stopwatch> getInstance();
Stopwatch(const Stopwatch&) = delete;
Stopwatch& operator=(const Stopwatch&) = delete;
```

**Minor Issue:**
- Using shared_ptr for singleton is unnecessary (could use unique_ptr internally)
- But this is acceptable design choice

#### 2.1.5 State Pattern
**Status: WELL IMPLEMENTED**

**Strengths:**
- ✅ `StateManager` (Context) manages state stack
- ✅ Abstract `state` base class
- ✅ Concrete states: `menuState`, `LevelState`, `pausedState`, `VictoryState`, `gameOverState`
- ✅ State stack implementation for pause/resume
- ✅ States pushed/popped appropriately
- ✅ `run()` method in each state
- ✅ State transitions handled by states themselves

**Architecture:**
```
StateManager (Context)
    └─ stack<unique_ptr<state>>
        ├─ menuState
        ├─ LevelState  
        ├─ pausedState
        ├─ VictoryState
        └─ gameOverState
```

**Minor Issues:**
- State receives many parameters in `run()` (window, event, manager, cam, wereld, deltaTime)
- Could benefit from a Context object to reduce parameter passing

### 2.2 Required Classes Implementation

#### 2.2.1 Game Class
**Status: GOOD**
- ✅ Manages SFML window creation
- ✅ Main game loop implemented
- ✅ Sets up StateManager
- ✅ Handles window events
- ✅ Delegates to StateManager
- ⚠️ Contains some logic that could be in states (window setup)

#### 2.2.2 Stopwatch Class
**Status: EXCELLENT**
- ✅ Singleton implementation
- ✅ Uses C++ chrono (not SFML Clock)
- ✅ `std::chrono::high_resolution_clock`
- ✅ `tick()` method updates deltaTime
- ✅ `getDeltaTime()` returns time between frames
- ✅ Multiple timers: lastTime, lastTimeEaten, lastChangedSprite, startFearMode
- ✅ Sprite animation timing
- ✅ Fear mode duration calculation
- ✅ Ghost spawn delay timing

#### 2.2.3 World Class
**Status: GOOD**
- ✅ Stores all entities (walls, collectables, ghosts, pacman)
- ✅ Orchestrates game logic
- ✅ Handles collisions
- ✅ Entity lifecycle management
- ✅ Reads from file for initialization
- ⚠️ Creates entities directly (needs factory)
- ⚠️ Collision detection uses basic rectangle intersection (custom implementation)

#### 2.2.4 Camera Class
**Status: EXCELLENT**
- ✅ Converts normalized coordinates [-1, 1] to pixels
- ✅ `worldToPixel()` method
- ✅ `distanceToPixelsHeight()` and `distanceToPixelsWidth()`
- ✅ `setDimensions()` for window resize
- ✅ No SFML dependencies (pure logic)
- ✅ Resolution-independent design

**Perfect implementation of the requirement!**

#### 2.2.5 Score Class
**Status: PARTIAL**
- ✅ Tracks score, lives, level
- ✅ Interacts with Stopwatch for time-based scoring
- ✅ Score multiplier based on eating speed
- ✅ Manages lives
- ✅ Triggers game over
- ✅ Level progression
- ❌ **No file I/O** for persistent high scores
- ❌ **No high score list** maintenance
- ⚠️ Observer pattern violation (holds view reference)

**Missing Implementation:**
```cpp
void saveHighScores(const std::string& filename);
void loadHighScores(const std::string& filename);
std::vector<int> getTopFiveScores();
```

#### 2.2.6 Random Class
**Status: EXCELLENT**
- ✅ Singleton implementation
- ✅ Uses `std::mt19937` (Mersenne Twister)
- ✅ Seeded with `std::random_device`
- ✅ `std::uniform_int_distribution` for uniform randomness
- ✅ Not using legacy `rand()`/`srand()`
- ✅ Single generator instance reused

**Perfect implementation!**

### 2.3 Code Quality Assessment

#### 2.3.1 Namespaces
**Status: GOOD**
- ✅ `logic` namespace for game logic
- ✅ `view` namespace for representation
- ✅ Clear modular separation
- ✅ Consistent usage throughout

#### 2.3.2 Exception Handling
**Status: MINIMAL**
- ✅ File reading wrapped in try-catch
- ✅ Throws `std::runtime_error` for missing files
- ⚠️ Limited use beyond file I/O
- ⚠️ No exception safety guarantees documented

```cpp
try {
    std::ifstream file(inputFile2);
    if (!file.is_open()) {
        throw std::runtime_error("Bestand bestaat niet: " + inputFile2);
    }
} catch (const std::exception& e) {
    std::cerr << "Fout: " << e.what() << std::endl;
    throw;
}
```

#### 2.3.3 Proper Keyword Usage
**Status: GOOD**
- ✅ `static` used correctly (Singleton getInstance, helper functions)
- ✅ `const` used extensively on getter methods
- ✅ `[[nodiscard]]` attributes on getters and query methods
- ✅ `override` keyword on virtual method overrides
- ✅ `final` on concrete classes (wall, coin, fruit, specific ghosts)
- ✅ `virtual` destructors declared
- ✅ `= default` for default implementations
- ✅ `= delete` for preventing copies

#### 2.3.4 Virtual Destructors
**Status: GOOD**
- ✅ Virtual destructors in base classes:
  - `entity::~entity() = default;`
  - `movableEntity::~movableEntity() = default;`
  - `Ghost::~Ghost() = default;`
  - `IObserver::~IObserver() = default;`
  - `state::~state() = default;`
- ✅ Prevents undefined behavior in polymorphic deletion

#### 2.3.5 Primitive Type Initialization
**Status: GOOD**
- ✅ Member initialization in constructors
- ✅ Member initializer lists used
- ✅ Default member initializers: `int score = 0;` style (though not always used)

```cpp
Score::Score(view::stateManeger& manager) 
    : IObserver(), score(0), livesLeft(2), level(1), manager(manager) {}
```

#### 2.3.6 Pass by Reference/Pointer
**Status: EXCELLENT**
- ✅ Const references for input parameters
- ✅ Smart pointers for ownership
- ✅ References for large objects (window, camera)
- ✅ Minimal copying

```cpp
void update(double deltaTime, std::vector<std::shared_ptr<entity>>& walls);
worldView(const std::shared_ptr<logic::world>& wereld, camera& camera, ...);
```

#### 2.3.7 Dynamic Casts
**Status: EXCELLENT**
- ✅ **No dynamic_cast found in codebase**
- ✅ Proper polymorphism used instead
- ✅ Pure virtual functions for behavior variation
- ✅ Specific methods on specific types when needed

#### 2.3.8 Code Duplication
**Status: GOOD**
- ✅ Base classes eliminate duplication (entity, movableEntity, Ghost)
- ✅ Helper methods for common operations
- ⚠️ Some duplication in view creation code (worldView constructor)
- ⚠️ Ghost view creation could use factory pattern

#### 2.3.9 Code Formatting (clang-format)
**Status: NOT VERIFIED**
- ⚠️ `.clang-format` file exists in repository
- ⚠️ Cannot verify if code is formatted without building
- ⚠️ Some inconsistencies visible (spacing, alignment)

#### 2.3.10 Code Comments and Documentation
**Status: EXCELLENT**
- ✅ Doxygen-style documentation on all classes
- ✅ `@class`, `@brief`, `@param`, `@return` tags
- ✅ Method documentation comprehensive
- ✅ Comments in Dutch (consistent, though English preferred in industry)
- ✅ Clear explanations of complex logic (fear mode duration formula)

Example:
```cpp
/**
 * @class Stopwatch
 * @brief Houdt alles van tijd bij in de game.
 */
```

#### 2.3.11 Smart Pointers
**Status: EXCELLENT**
- ✅ **Mandatory smart pointer usage fulfilled**
- ✅ `std::shared_ptr` for shared ownership
- ✅ `std::unique_ptr` for exclusive ownership (State stack)
- ✅ `std::weak_ptr` used in views (wallView)
- ✅ No raw pointers for ownership
- ✅ Raw references only for non-owning access (window, camera)

**Ownership Model:**
```cpp
// Shared ownership: multiple references
std::shared_ptr<logic::world> wereld
std::shared_ptr<Ghost> _redGhost

// Exclusive ownership: state stack
std::stack<std::unique_ptr<view::state>> stack

// Weak references: observers
std::weak_ptr<logic::wall> wallModel
```

**Minor Issue:**
- Model-to-View references should ideally be weak_ptr, not shared_ptr
- But this is consistent with their (incorrect) observer pattern

### 2.4 Architecture and Separation of Concerns

#### 2.4.1 Logic Library Separation
**Status: CRITICAL FAILURE**

**Requirement:**
> "Encapsulate the game logic into a standalone (static or dynamic) library using CMake"
> "You should be able to compile this logic library without having SFML installed"

**Issues:**
1. ❌ **No separate logic library in CMakeLists.txt**
   - Everything compiled into single executable
   - No `add_library(logic ...)` statement
   - No separation in build system

2. ❌ **Logic depends on SFML types**
   - `observer.h` includes `<SFML/Graphics.hpp>`
   - `IObserver` in logic code (should be abstract)
   - `view::Observer` requires SFML RenderWindow
   
3. ❌ **Model includes View headers**
   - `entity.h` includes `view/entities/entityView.h`
   - `movableEntity.h` includes `view/entities/movableEntityView.h`
   - `collectable.h` includes `view/entities/collectableView.h`

**Current CMakeLists.txt:**
```cmake
add_executable(packman main.cpp
    code/game.cpp
    code/logic/world.cpp
    # ... all files together
)
target_link_libraries(packman sfml-graphics sfml-window sfml-system)
```

**Required Structure:**
```cmake
# Logic library (no SFML)
add_library(packman_logic STATIC
    code/logic/world.cpp
    code/logic/entities/entity.cpp
    # ... only logic files
)

# Representation executable
add_executable(packman main.cpp
    code/game.cpp
    code/view/worldView.cpp
    # ... view files
)
target_link_libraries(packman packman_logic sfml-graphics sfml-window sfml-system)
```

**Impact:** This is a **critical architectural failure** that violates the core requirement.

#### 2.4.2 Cohesion and Coupling

**Coupling: HIGH (POOR)**
- ❌ Logic tightly coupled to View through includes
- ❌ Models hold references to specific view types
- ❌ Cannot use logic without view
- ✅ Entity hierarchy well-designed
- ✅ State pattern reduces coupling between states

**Cohesion: MEDIUM**
- ✅ Each class has single responsibility
- ✅ Entity classes focused on entity behavior
- ✅ Stopwatch focused on timing
- ⚠️ World class has many responsibilities (could be split)
- ⚠️ State run() methods do multiple things

### 2.5 Design Principles

#### SOLID Principles Assessment:

**Single Responsibility Principle: MOSTLY GOOD**
- ✅ Most classes have single responsibility
- ⚠️ World class orchestrates many things
- ⚠️ State run() methods handle multiple concerns

**Open/Closed Principle: GOOD**
- ✅ Entity hierarchy extensible through inheritance
- ✅ Ghost types can be added without modifying base
- ✅ State pattern allows new states without modifying manager
- ✅ Pure virtual functions enforce behavior

**Liskov Substitution Principle: GOOD**
- ✅ Derived classes properly substitute base classes
- ✅ Ghost hierarchy maintains contracts
- ✅ No violations observed

**Interface Segregation Principle: GOOD**
- ✅ Interfaces focused (IObserver, entity, movableEntity)
- ✅ No fat interfaces forcing implementation of unused methods

**Dependency Inversion Principle: VIOLATED**
- ❌ High-level logic depends on low-level view details
- ❌ Models depend on concrete view types
- ❌ No abstract factory to invert dependencies
- ✅ Uses interfaces where present (IObserver)

**Score: 22/40**

**Major Issues:**
1. Critical: No Abstract Factory implementation (-8)
2. Critical: No library separation in CMake (-5)
3. Critical: MVC pattern violated (logic knows view) (-4)
4. Major: Observer pattern implemented backwards (-3)
5. Major: No persistent score storage (-3)

---

## 3. Visuals and Aesthetics (Not Graded in Code Review)

**Note:** Visual implementation requires SFML to run and build. Based on code structure:
- ✅ Sprite loading infrastructure present
- ✅ Animation logic in views (sprite change timing)
- ✅ Direction-based sprite selection
- ✅ Fear mode visual changes (ghost color)
- ⚠️ Cannot verify actual sprites without running

---

## 4. Technical Requirements Summary

### 4.1 Build System (CMake)
**Status: INCOMPLETE**
- ✅ CMakeLists.txt present
- ✅ C++17 standard set
- ✅ SFML dependencies specified
- ❌ **No separate logic library**
- ❌ **Logic not independent of SFML**
- ⚠️ Typo: `SFML_INDCLUDE_DIR` (should be `SFML_INCLUDE_DIR`)

### 4.2 Code Organization
**Status: GOOD**
- ✅ Clear directory structure
- ✅ `code/logic/` for game logic
- ✅ `code/view/` for representation
- ✅ Entities organized in subdirectories
- ✅ Header/implementation separation

### 4.3 Memory Management
**Status: EXCELLENT**
- ✅ Smart pointers throughout
- ✅ No memory leaks expected (RAII)
- ✅ Proper ownership semantics
- ✅ Virtual destructors prevent UB

---

## 5. Areas for Improvement

### 5.1 Critical Improvements Required

1. **Implement Abstract Factory Pattern** ⚠️ HIGH PRIORITY
   ```cpp
   // Create AbstractFactory in logic library
   // Create ConcreteFactory in view library
   // Use factory to create entities with views attached
   ```

2. **Fix Library Separation** ⚠️ HIGH PRIORITY
   ```cmake
   # Separate CMake targets
   # Logic library should not depend on SFML
   # Remove view includes from logic headers
   ```

3. **Fix Observer Pattern** ⚠️ HIGH PRIORITY
   ```cpp
   // Subject maintains observer list
   // Observers hold weak_ptr to subjects
   // Remove view references from models
   ```

4. **Implement Score Persistence** ⚠️ HIGH PRIORITY
   ```cpp
   void Score::saveHighScores(const std::string& filename);
   void Score::loadHighScores(const std::string& filename);
   // Display top 5 in menu state
   ```

5. **Fix MVC Violation** ⚠️ HIGH PRIORITY
   ```cpp
   // Models should not know about views
   // Use abstract IObserver only
   // Views hold weak references to models
   ```

### 5.2 Design Improvements

1. **Reduce World Class Responsibilities**
   - Consider EntityManager for entity lifecycle
   - Separate CollisionDetector
   - Separate InputHandler

2. **Improve State Context**
   - Create StateContext struct to reduce parameter passing
   - Bundle window, camera, world, deltaTime

3. **Factory for View Creation**
   - Reduce duplication in worldView constructor
   - Use factory method or builder pattern

4. **Better Error Handling**
   - More exception types
   - Exception safety guarantees
   - RAII for all resources

### 5.3 Code Quality Improvements

1. **Documentation**
   - Consider English comments (industry standard)
   - Add more inline comments for complex algorithms
   - Document design decisions

2. **Testing**
   - No unit tests found
   - Add tests for logic library
   - Test ghost AI behavior
   - Test collision detection

3. **Configuration**
   - Extract magic numbers to constants
   - Configuration file for game parameters
   - Easier difficulty tuning

4. **Const Correctness**
   - More const methods
   - Const references where possible

### 5.4 Performance Considerations

1. **Entity Storage**
   - Consider spatial partitioning for collision detection
   - Current O(n) collision checks could be optimized

2. **Smart Pointer Overhead**
   - Some shared_ptr could be unique_ptr
   - Consider object pools for frequent allocations

---

## 6. Positive Aspects

Despite the issues, the project demonstrates many strengths:

### 6.1 Excellent Implementations

1. ✅ **Stopwatch Class** - Perfect use of C++ chrono, singleton pattern
2. ✅ **Random Class** - Correct modern C++ random number generation
3. ✅ **Camera Class** - Clean coordinate transformation, no dependencies
4. ✅ **Smart Pointer Usage** - Consistent and correct throughout
5. ✅ **State Pattern** - Well-implemented FSM with stack
6. ✅ **Entity Hierarchy** - Good use of inheritance and polymorphism
7. ✅ **Ghost AI** - Complex behavior implemented correctly
8. ✅ **Documentation** - Comprehensive Doxygen-style comments
9. ✅ **No Dynamic Casts** - Proper polymorphism instead
10. ✅ **Virtual Destructors** - All base classes have them

### 6.2 Good Design Choices

1. Normalized coordinate system for logic
2. Time-based scoring multiplier
3. Difficulty scaling formula
4. Entity inheritance hierarchy
5. Namespace organization
6. Fear mode duration calculation
7. Delta time for frame-rate independence

---

## 7. Estimated Grade

### Breakdown by Criteria:

| Criterion | Weight | Score | Weighted Score |
|-----------|--------|-------|----------------|
| **Core Game Requirements** | 40% | 70% | 28.0% |
| - Missing persistent scoreboard | | -15% | |
| - Missing menu scoreboard display | | -15% | |
| - All other features present | | | |
| **Design and Code Quality** | 40% | 55% | 22.0% |
| - No Abstract Factory | | -20% | |
| - No library separation | | -12% | |
| - Observer pattern backwards | | -8% | |
| - MVC violated | | -10% | |
| - Good: Smart pointers, singletons, state | | +15% | |
| **Defence/Documentation** | 10% | 85% | 8.5% |
| - Excellent code comments | | +5% | |
| - Clear structure | | | |
| **Report** | 10% | N/A | 8.0% |
| - Assuming adequate report | | | |

### **Total Estimated Grade: 66.5/100**

### Grade Interpretation:

**D+ to C- Range (66.5%)**

The project demonstrates solid programming skills and understanding of C++ concepts, but fails to meet several critical architectural requirements:

1. **No Abstract Factory** - Required pattern completely absent
2. **No library separation** - Core requirement not met
3. **Backwards Observer** - Pattern implemented incorrectly  
4. **MVC violation** - Logic depends on View
5. **No score persistence** - Missing gameplay feature

**If Critical Issues Were Fixed:**
- With proper factory and library separation: **+10%** → 76.5% (C+)
- With fixed observer pattern: **+5%** → 81.5% (B-)
- With score persistence: **+3%** → 84.5% (B)

**Best Case with All Fixes: ~85% (B)**

---

## 8. Recommendations for Student

### Immediate Actions:

1. **Implement Abstract Factory (3-4 hours)**
   - Create AbstractFactory interface in logic
   - Create ConcreteFactory in view
   - Refactor entity creation to use factory

2. **Separate Logic Library (2-3 hours)**
   - Modify CMakeLists.txt to create separate library
   - Remove SFML includes from logic
   - Make IObserver truly abstract

3. **Add Score Persistence (1-2 hours)**
   - Implement file I/O in Score class
   - Save/load high scores
   - Display in menu state

4. **Fix Observer Pattern (3-4 hours)**
   - Move observer references to views
   - Models maintain abstract observer lists
   - Break circular dependencies

### For Future Projects:

1. Start with architecture - design before coding
2. Create CMake structure early
3. Test library separation early
4. Review design patterns carefully
5. Implement mandatory patterns first
6. Add automated tests
7. Use CI to catch issues early

---

## 9. Conclusion

This project demonstrates **good programming skills** and **solid C++ knowledge**, with excellent implementation of individual components (Stopwatch, Random, Camera, Smart Pointers, Documentation). The game logic itself is well-structured with proper entity hierarchies and complex AI behavior.

However, the project has **critical architectural flaws** that prevent it from meeting the core requirements:
- Missing Abstract Factory pattern (required)
- No library separation (required)
- Incorrect Observer implementation
- MVC violation (logic knows view)
- Missing score persistence

These are not minor issues - they directly violate stated project requirements. The design makes it impossible to use the logic library independently or switch graphics libraries, which was an explicit goal.

**The student shows promise** and with focused effort on proper architecture and design patterns, could significantly improve the grade. The good news is that most critical issues are fixable with targeted refactoring.

### Final Assessment: **66.5/100 (D+ to C-)**

**With recommended fixes: 80-85/100 (B- to B)**

---

## Appendix: Checklist of Requirements

### Design Patterns (Required)
- [ ] **Abstract Factory** - Not implemented ❌
- [x] **Observer** - Implemented incorrectly ⚠️
- [x] **Singleton** - Correctly implemented ✅
- [x] **State** - Well implemented ✅
- [ ] **MVC** - Violated ❌

### Required Classes
- [x] **Game** - Present ✅
- [x] **Stopwatch** - Excellent ✅
- [x] **World** - Good ✅
- [x] **Camera** - Excellent ✅
- [ ] **Score** - Missing persistence ⚠️
- [x] **Random** - Excellent ✅

### Architecture
- [ ] **Logic Library Separation** - Not implemented ❌
- [ ] **No SFML in Logic** - Violated ❌
- [x] **Namespace usage** - Good ✅

### Code Quality
- [x] **Smart pointers** - Excellent ✅
- [x] **Virtual destructors** - Present ✅
- [x] **const/static/override** - Good ✅
- [x] **No dynamic_cast** - Excellent ✅
- [x] **Documentation** - Excellent ✅
- [ ] **Exception handling** - Minimal ⚠️

### Game Features
- [ ] **Scoreboard at startup** - Missing ❌
- [ ] **Persistent high scores** - Missing ❌
- [x] **Pac-Man controls** - Working ✅
- [x] **Ghost AI** - All types present ✅
- [x] **Fear mode** - Working ✅
- [x] **Level progression** - Working ✅
- [x] **Lives system** - Working ✅
- [x] **Time-based scoring** - Working ✅

---

*Review completed: December 2025*
*Reviewer: Senior Software Engineer with expertise in C++ and software architecture*
