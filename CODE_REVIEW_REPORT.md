# Comprehensive Code Review Report
## Pac-Man Game Project - Advanced Programming Course

**Student:** Niels Hertoghs  
**Review Date:** December 13, 2025  
**Project:** Pac-Man Game Implementation in C++  
**Total Lines of Code:** ~4,352 lines

---

## Executive Summary

This report provides a comprehensive, critical review of the Pac-Man game implementation based on the assignment requirements for the Advanced Programming course. The review evaluates code design, implementation of design patterns, code quality, adherence to design principles (cohesion and coupling), and overall project completeness.

**Overall Assessment:** The project demonstrates significant effort and understanding of core concepts, but exhibits several critical architectural violations and design principle issues that prevent it from achieving a high grade.

---

## 1. Core Gameplay Requirements (40%)

### ✅ Implemented Features
- ✓ **Game Startup & Initialization:** Menu state with scoreboard display
- ✓ **Maze Representation:** File-based maze loading system
- ✓ **Player Controls:** Continuous movement with direction change handling
- ✓ **Collision Detection:** Basic wall collision detection
- ✓ **Ghost Movement and AI:** Four ghosts with different behaviors
  - Red ghost: Random direction with probability-based selection
  - Manhattan-based ghosts (Blue, Green, Orange)
- ✓ **Coin Collection:** Scoring system with time-based multipliers
- ✓ **Fruits:** Fear mode activation functionality
- ✓ **Multiple Lives:** Three lives system with death handling
- ✓ **Level Progression:** Next level functionality with difficulty scaling
- ✓ **Score System:** Time-based score calculation

### ⚠️ Issues and Gaps
1. **Ghost AI Implementation:**
   - The random ghost (red) implementation doesn't properly implement the "locked direction" behavior specified in requirements
   - Manhattan distance calculations are present but the "front of Pac-Man" logic appears incomplete
   - Ghost spawn timing (5 sec, 10 sec delays) is implemented via `canStartAfter5Sec()` and `canStartAfter10Sec()`

2. **Fear Mode:**
   - Implementation exists but review reveals potential issues with ghost behavior during fear mode
   - The reversal and escape logic needs verification

3. **Animation:**
   - Sprite animation system is present (`changeSprite()` method) but implementation details need verification
   - Animation tied to stopwatch timing (0.1s intervals)

**Score for Core Functionality: 32/40**
- Most features are present but several behavioral requirements are not fully met
- Missing or incomplete implementation of specific ghost AI behaviors

---

## 2. Code Design and Architecture (40%)

This section critically evaluates the project's adherence to required design patterns and architectural principles.

### 2.1 Model-View-Controller (MVC) Pattern

#### ✅ Strengths:
- Clear separation between `logic` and `view` namespaces
- Model classes (entities) are separate from View classes (entityView hierarchy)
- World class acts as a controller managing entity interactions

#### ❌ Critical Issues:

**VIOLATION #1: Logic-View Coupling**
```cpp
// File: code/logic/entities/entity.h (Lines 9)
#include "../../view/entities/entityView.h"
```
The **logic layer directly includes view headers**, which is a severe violation of MVC separation. Logic should never depend on view types.

**VIOLATION #2: Observer Pattern Implementation**
```cpp
// File: code/logic/entities/movableEntity.h (Lines 30)
std::shared_ptr<view::movableEntityView> observer;
```
Logic classes store **concrete view types** as observers. This creates tight coupling between model and view layers.

**VIOLATION #3: Missing Controller Abstraction**
The `world` class mixes controller responsibilities with entity management. There's no clear separation between:
- Game state orchestration
- Entity lifecycle management
- Input handling translation

**Impact:** This violates the fundamental MVC principle. The logic library cannot be compiled independently of SFML, defeating a primary project requirement.

### 2.2 Observer Pattern

#### ✅ Strengths:
- Observer interface defined (`IObserver`)
- Notification enum system (`notifications`)
- Multiple observers subscribe to subjects

#### ❌ Critical Issues:

**VIOLATION #4: Concrete View Types in Logic**
```cpp
// File: code/logic/entities/collectable.h (Line 22)
std::shared_ptr<view::collectableView> collectableObserver;
```
Instead of storing generic `IObserver`, logic stores **concrete view types**, creating unnecessary coupling.

**VIOLATION #5: Score Observer Violation**
```cpp
// File: code/logic/Score.h (Lines 26-27)
std::shared_ptr<view::ScoreView> scoreObserver;
view::stateManeger& manager;
```
The `Score` class (in logic layer):
- Stores reference to `stateManeger` (view layer)
- Directly changes states via `manager.prevState()` and `manager.pushState()`
- This is a **severe architectural violation** - logic should not control view state

**Correct Implementation:**
Logic should notify observers of events (e.g., GAME_OVER, LEVEL_COMPLETE), and the view layer should decide state transitions.

### 2.3 Abstract Factory Pattern

#### ✅ Strengths:
- Abstract factory interfaces defined (`LogicFactory`, `ViewFactory`)
- Concrete implementations present
- Factory creates appropriate entity types based on parameters

#### ❌ Critical Issues:

**VIOLATION #6: Factory Pattern Not Used Correctly**
```cpp
// File: code/logic/world.cpp (Line 39)
std::unique_ptr<ConcreteLogicFactory> factory = std::make_unique<ConcreteLogicFactory>();
```
The `World` class directly instantiates `ConcreteLogicFactory` rather than receiving it through dependency injection. This defeats the purpose of the factory abstraction.

**VIOLATION #7: No Factory Injection**
The assignment states: *"the Game class provides a pointer to this concrete factory to the World"*. 

Current implementation in `game.cpp`:
```cpp
std::shared_ptr<logic::world> wereld = std::make_shared<logic::world>("input_output/map.txt");
```
The world is created without factory injection. The factory is instantiated **inside** world, not provided by Game.

**VIOLATION #8: ViewFactory Not Used by Logic**
The `ViewFactory` exists but is instantiated and used only in view layer code. The abstract factory pattern should allow logic to create entities with views attached without knowing concrete view types.

### 2.4 Singleton Pattern

#### ✅ Strengths:
- `Stopwatch` implemented as singleton
- `random` implemented as singleton
- Both use shared_ptr for instance management
- Copy constructor and assignment operator deleted

#### ⚠️ Issues:

**Design Concern #1: Thread Safety**
```cpp
// File: code/logic/Stopwatch.cpp (Lines 9-14)
std::shared_ptr<Stopwatch> Stopwatch::getInstance() {
    if (!_instance) {
        _instance = std::shared_ptr<Stopwatch>(new Stopwatch());
    }
    return _instance;
}
```
This is **not thread-safe**. In C++11+, static local variables are thread-safe, but this implementation using a static member is not.

**Design Concern #2: Singleton Necessity**
While singletons are required by the assignment, `Stopwatch` contains game state (last eaten time, sprite changes) that might need to be reset between games. The current implementation makes this awkward.

### 2.5 State Pattern

#### ✅ Strengths:
- State interface defined with virtual methods
- Multiple concrete states: `menuState`, `LevelState`, `pausedState`, `gameOverState`, `VictoryState`
- State stack implementation in `stateManeger`
- State transitions implemented

#### ❌ Critical Issues:

**VIOLATION #9: State Responsibilities**
```cpp
// File: code/view/state_maneger/state.h (Lines 48-51)
virtual std::pair<std::vector<sf::Text>, std::vector<sf::RectangleShape>> run(
    sf::RenderWindow& window, sf::Event& event, stateManeger& manager, 
    camera& cam, std::shared_ptr<logic::world> wereld, const float& deltaTime) = 0;
```
Problems:
- States **receive the state manager** as parameter and call methods on it
- This creates circular dependency (manager knows states, states know manager)
- States should return "state transition requests" not directly manipulate the manager

**VIOLATION #10: World as Parameter**
Every state receives `std::shared_ptr<logic::world> wereld` as parameter, but most states don't need it. This violates the Interface Segregation Principle.

**Design Issue #1: State Stack vs. Simple State Machine**
The assignment suggests a state stack for pause functionality. Implementation uses a stack, but the design doesn't clearly leverage stack benefits beyond pause/resume.

### 2.6 Required Key Classes

#### ✅ Game Class
- Present and initializes window, camera, state manager
- Manages main game loop
- **Issue:** Doesn't properly inject factories into world

#### ✅ Stopwatch Class
- Implemented using C++ chrono (not SFML Clock) ✓
- Tracks delta time ✓
- Multiple time tracking features ✓

#### ⚠️ World Class
- Stores all entities ✓
- Manages collisions ✓
- **Issue:** Directly instantiates factory instead of receiving it
- **Issue:** Update method is quite large (148 lines) with multiple responsibilities

#### ✅ Camera Class
- Implements coordinate transformation ✓
- Normalized coordinates (-1 to 1) ✓
- No SFML dependencies in logic ✓

#### ⚠️ Score Class
- Manages score, lives, level ✓
- File I/O for high scores ✓
- **CRITICAL:** Directly manipulates state manager (architectural violation)

#### ✅ Random Class
- Uses Mersenne Twister ✓
- Singleton pattern ✓
- Proper C++ random facilities ✓

### 2.7 Separation of Logic and Representation

#### ❌ CRITICAL FAILURE

**VIOLATION #11: Logic Library Not Separate**

The assignment explicitly requires:
> "encapsulate the game logic into a standalone (static or dynamic) library using CMake"

Current `CMakeLists.txt`:
```cmake
add_executable(packman main.cpp
    code/game.cpp
    code/view/state_maneger/stateManeger.cpp
    # ... all files including both logic and view in one executable
)
```

**There is NO separate logic library.** All files are compiled into a single executable. This is a fundamental requirement violation.

**Correct Implementation Should Have:**
```cmake
# Logic library (no SFML dependency)
add_library(packman_logic STATIC
    code/logic/world.cpp
    code/logic/entities/*.cpp
    # ... only logic files
)

# Main executable linking to logic
add_executable(packman 
    main.cpp
    code/game.cpp
    code/view/*.cpp
)
target_link_libraries(packman packman_logic sfml-graphics sfml-window sfml-system)
```

**Why This Matters:**
- Cannot verify logic compiles without SFML
- Cannot write unit tests for logic without SFML
- Cannot reuse logic with different rendering libraries
- Defeats the entire purpose of the architectural requirements

### Summary of Design Pattern Issues

| Pattern | Implementation | Grade | Critical Issues |
|---------|---------------|-------|-----------------|
| MVC | Partial | 50% | Logic-view coupling, direct view includes |
| Observer | Poor | 40% | Concrete view types in logic, wrong notification direction |
| Abstract Factory | Poor | 30% | Not used for dependency injection, factory in wrong layer |
| Singleton | Good | 80% | Thread safety concerns |
| State | Fair | 60% | Circular dependencies, poor responsibility division |
| **Separation** | **Failed** | **0%** | **No separate logic library** |

**Score for Code Design: 12/40**
- Fundamental architectural requirements not met
- Design patterns present but incorrectly implemented
- Severe coupling between logic and view layers

---

## 3. Code Quality (Combined with Design - 40% total)

### 3.1 Use of C++ Features

#### ✅ Strengths:
- **Smart Pointers:** Consistent use throughout (`std::shared_ptr`, `std::unique_ptr`)
- **Namespaces:** Clear `logic` and `view` namespaces
- **const correctness:** Many methods marked `const`, `[[nodiscard]]` used appropriately
- **override keyword:** Consistently used in derived classes
- **C++ chrono:** Proper use for time management
- **Exception Handling:** try-catch blocks for file operations
- **Modern random:** Mersenne Twister instead of rand/srand

#### ❌ Issues:

**Issue #1: Unnecessary std::move()**
```cpp
// File: code/view/ViewFactory.cpp (Line 45)
return std::move(PacmanView);
```
Returning local variables already uses move semantics. Explicit `std::move()` here is redundant and prevents copy elision.

**Issue #2: Raw Pointer Usage**
```cpp
// File: code/observer.h (Line 30)
sf::RenderWindow& window;
```
While references are acceptable, the Observer classes store references to window and camera. This creates lifetime dependencies that aren't explicitly managed.

**Issue #3: Missing Virtual Destructors**
Most classes have `= default` virtual destructors, which is good. However, `BaseFactory` has a virtual destructor, which is correct.

**Issue #4: Memory Management**
No obvious memory leaks detected in the reviewed code. Smart pointers are used consistently.

### 3.2 Cohesion and Coupling

#### Cohesion Analysis:

**Low Cohesion Classes:**

1. **Stopwatch Class**
```cpp
// Multiple unrelated responsibilities:
- Delta time tracking (tick(), getDeltaTime())
- Eaten collectable timing (eatCollectable())
- Sprite animation timing (changeSprite())
- Ghost spawn timing (canStartAfter5Sec(), canStartAfter10Sec())
- Fear mode timing (startFearMode(), isFearDone())
```
This class has **poor cohesion** - it manages 5 different time-related concerns that could be separated.

2. **World Class**
- Entity storage
- Entity creation (via factory)
- Collision detection
- Game state updates
- Fear mode coordination
- Level progression logic

The World class tries to do too much. Collision detection could be a separate system, game state management could be separated.

3. **Score Class**
- Score calculation
- Lives management
- Level tracking
- High score file I/O
- **State management** (!)

The Score class **directly manages UI states**, which is completely outside its domain.

**High Cohesion Classes:**
- `Camera`: Single responsibility - coordinate transformation
- `random`: Single responsibility - random number generation
- Entity classes (wall, coin, fruit): Single, well-defined purposes

#### Coupling Analysis:

**Tight Coupling Problems:**

1. **Logic → View Coupling** (Already discussed)
   - Logic includes view headers
   - Logic stores view types
   - **Severity:** CRITICAL

2. **Score → StateManager Coupling**
```cpp
// File: code/logic/Score.h (Line 27)
view::stateManeger& manager;
```
   - Score (logic) depends on state manager (view)
   - Score directly controls state transitions
   - **Severity:** CRITICAL

3. **Ghost → Pacman Coupling**
```cpp
// File: code/logic/entities/manhattanGhost.h (Line 16)
std::shared_ptr<Pacman> pacman;
```
   - Ghosts store reference to Pacman
   - While this is necessary for AI, it creates tight coupling
   - Better: Ghosts receive Pacman position as parameter to update()
   - **Severity:** MODERATE (design choice, but not ideal)

4. **Entity → View Coupling**
```cpp
// File: code/logic/entities/entity.h (Line 9)
#include "../../view/entities/entityView.h"
```
   - Entity headers include view headers even when not needed
   - **Severity:** HIGH

### 3.3 Code Style and Documentation

#### ✅ Strengths:
- **Doxygen Comments:** Comprehensive API documentation with `@brief`, `@param`, `@return`
- **Consistent Naming:** camelCase for variables, PascalCase for classes
- **Header Guards:** All headers use include guards
- **Forward Declarations:** Used in some places to reduce compilation dependencies

#### ⚠️ Issues:

**Issue #1: Inconsistent Language**
```cpp
// Dutch comments mixed with English:
// "De observer van de movableEntity" (Dutch)
// "The observer of the movableEntity" (would be English)
```
While the code itself is in English, many comments are in Dutch. For an academic project, this is acceptable, but inconsistent.

**Issue #2: clang-format**
The assignment requires using clang-format with a specific configuration. Cannot verify if code is properly formatted without running the tool, but a `.clang-format` file is present.

**Issue #3: Magic Numbers**
```cpp
// File: code/logic/world.cpp
double y = 1.0 - 2.0 / 7.0;
x += 0.1;
y -= 1.0 / 7.0;

// File: code/logic/entities/movableEntity.cpp
double width = 1.f / 10.f;
double height = 1.f / 7.f;
```
Many magic numbers related to grid coordinates. These should be named constants.

**Issue #4: Long Methods**
```cpp
// File: code/logic/world.cpp - update() method is 148 lines
// File: code/view/state_maneger/state.cpp - run() methods are very long
```
These methods have multiple responsibilities and should be refactored into smaller, focused methods.

### 3.4 Polymorphism and Templates

#### Polymorphism:
- **Good usage** in entity hierarchy (entity → movableEntity → Pacman/Ghost)
- **Good usage** in collectable hierarchy (collectable → coin/fruit)
- **Good usage** in ghost hierarchy (Ghost → manhattanGhost → specific ghosts)
- **Good usage** in view hierarchy (Observer → entityView → specific views)
- **Good usage** in state pattern

No evidence of dynamic_cast abuse. Type resolution done through virtual methods.

#### Templates:
**Not used in the project.** The assignment mentions templates as a potential bonus extension. No template code found.

### 3.5 Additional Requirements

#### ✅ Implemented:
- Exception handling for file operations ✓
- const keyword usage ✓
- override keyword usage ✓
- Virtual destructors ✓
- No unnecessary copying (references used) ✓
- Smart pointers throughout ✓
- Primitive types initialized ✓

#### ❌ Not Verified:
- **Memory leak check with valgrind:** Cannot run without SFML installation
- **clang-format compliance:** .clang-format present but not verified

**Score for Code Quality: 24/40** (when combined with design)
- Good C++ practices in many areas
- Poor cohesion in several key classes
- Critical coupling issues
- Good documentation

---

## 4. CMake and Build System

### Requirements:
- Separate logic library (static or dynamic)
- Link representation with logic library
- Logic should compile without SFML

### ❌ Critical Failure:

**VIOLATION #12: No Separate Logic Library**

As discussed in section 2.7, the CMakeLists.txt does not create a separate logic library. All code is compiled into a single executable.

**Current Structure:**
```
add_executable(packman [all files])
target_link_libraries(packman sfml-graphics sfml-window sfml-system)
```

**Required Structure:**
```
add_library(packman_logic [logic files only])
add_executable(packman [view files + main])
target_link_libraries(packman packman_logic sfml-graphics ...)
```

This is a **fundamental requirement violation** that affects:
- Project architecture evaluation
- Testing capability
- Code reusability
- Grading criteria

---

## 5. CircleCI Configuration

### ✅ Present:
- `.circleci/config.yml` exists
- Builds project using Ubuntu 20.04
- Installs SFML, CMake, g++
- Runs build steps

### ⚠️ Issues:

**Issue #1: No Test Execution**
The CI only builds the project, doesn't run tests. While the assignment doesn't explicitly require tests, CI typically should verify the build works correctly.

**Issue #2: Uses Ubuntu 20.04 instead of 24.04**
Assignment specifies Ubuntu 24.04, but CI uses 20.04. This might cause compatibility issues.

**Issue #3: No Artifact Generation**
While it stores artifacts, there's no verification step that the executable actually works.

---

## 6. Areas for Improvement

### Critical (Must Fix):
1. **Create separate logic library in CMake** - This is a fundamental requirement
2. **Remove all logic → view dependencies** - Logic must not include view headers
3. **Fix Observer pattern** - Use abstract observers in logic, not concrete view types
4. **Fix Score → StateManager coupling** - Score should emit events, not control states
5. **Implement proper factory injection** - World should receive factory, not create it

### High Priority:
6. **Refactor Stopwatch class** - Separate concerns into multiple classes
7. **Refactor World class** - Extract collision detection, reduce responsibilities
8. **Fix State pattern** - States should return transition requests, not call manager
9. **Remove magic numbers** - Use named constants for grid dimensions

### Medium Priority:
10. **Improve ghost AI** - Verify "locked direction" behavior for red ghost
11. **Add thread safety to singletons** - Use Meyer's singleton pattern
12. **Reduce method lengths** - Break down large methods into smaller functions
13. **Improve Ghost-Pacman coupling** - Pass position as parameter instead of storing reference

### Low Priority (Enhancements):
14. **Add unit tests** - Test logic layer independently
15. **Use templates** - Could improve factory pattern implementation
16. **Add more design patterns** - Command pattern for input, Strategy for ghost AI
17. **Consistent language** - All comments in English or all in Dutch
18. **Update CI to Ubuntu 24.04** - Match reference platform

---

## 7. Positive Aspects

Despite the critical issues, the project demonstrates several strengths:

1. **Comprehensive Feature Implementation:** Most gameplay features are present
2. **Good Use of Smart Pointers:** Memory management is sound
3. **Consistent Documentation:** Doxygen comments throughout
4. **Modern C++:** Uses C++17 features appropriately
5. **Proper Random Number Generation:** Mersenne Twister implementation
6. **Exception Handling:** File operations have error handling
7. **Entity Hierarchy:** Well-structured inheritance for game objects
8. **Ghost AI Variety:** Multiple ghost types with different behaviors
9. **Time-based Scoring:** Sophisticated scoring system
10. **Level Progression:** Difficulty scaling implemented

---

## 8. Estimated Grade Breakdown

Based on the assignment criteria:

### Core Game Requirements (40%): 32/40 = **32%**
- Most features implemented (80%)
- Some behavioral requirements not fully met (deduction of 8%)

### Good Design and Code Quality (40%): 12/40 = **12%**
- Design patterns present but incorrectly implemented (30%)
- Critical architectural violations:
  - No separate logic library (0% for this requirement)
  - Logic-view coupling (major deduction)
  - Observer pattern misuse (major deduction)
  - Factory pattern not properly used (deduction)
- Some good C++ practices (+12%)

### Project Defense (10%): Not Evaluated = **?/10**
- Requires video review (not part of this code review)

### Documentation (10%): 7/10 = **7%**
- Code comments present and comprehensive (+5%)
- No written report yet (would need to be evaluated separately)
- Some documentation issues (-3%)

### Bonus Points (10%): 0/10 = **0%**
- No additional design patterns beyond required
- No technical extensions (templates, multi-threading)
- No significant creative features beyond requirements

### **Estimated Total: 51/100**

### Grade Interpretation:
- With perfect defense and documentation: ~58-60/100
- With good bonus features: Could reach 65-70/100
- **Without fixing critical architectural issues: Maximum ~60/100**
- **With fixed architecture: Could reach 75-85/100**

---

## 9. Critical Issues Summary

The following issues **must be addressed** to meet minimum project requirements:

1. ❌ **NO SEPARATE LOGIC LIBRARY** - Fundamental requirement not met
2. ❌ **Logic depends on View** - Violates MVC and project architecture
3. ❌ **Score class controls StateManager** - Wrong layer, wrong responsibility
4. ❌ **Factory pattern misused** - No dependency injection
5. ❌ **Observer pattern incorrect** - Concrete view types in logic

These are not minor code quality issues. These are **architectural violations** that demonstrate misunderstanding of the fundamental project requirements.

---

## 10. Recommendations

### To Achieve Passing Grade (60/100):
1. Create separate logic library in CMake
2. Remove all view dependencies from logic
3. Fix Observer pattern to use abstract observers
4. Write a proper project report explaining design choices

### To Achieve Good Grade (75/100):
All of the above, plus:
5. Fix factory pattern implementation
6. Refactor Score class to not control states
7. Improve cohesion in Stopwatch and World classes
8. Fix all coupling issues

### To Achieve Excellent Grade (85+/100):
All of the above, plus:
9. Add bonus features (sounds, better AI, additional patterns)
10. Demonstrate exceptional understanding in defense video
11. Add comprehensive unit tests
12. Perfect code quality throughout

---

## 11. Conclusion

This Pac-Man implementation demonstrates **significant programming effort** and **functional completeness**, with most gameplay features working. The student clearly understands object-oriented programming and has attempted to implement all required design patterns.

However, the project suffers from **critical architectural violations** that undermine its core educational objectives:

1. **The logic library is not separated from the view**, violating a fundamental requirement
2. **The MVC pattern is compromised** by logic-view coupling
3. **Design patterns are present but incorrectly implemented**, showing surface-level understanding

The code quality itself is reasonable - good use of modern C++, smart pointers, documentation - but these positives cannot compensate for the architectural problems.

### Final Assessment:

**Technical Implementation:** ⭐⭐⭐☆☆ (3/5) - Works but has architectural issues  
**Design Patterns:** ⭐⭐☆☆☆ (2/5) - Present but incorrectly implemented  
**Code Quality:** ⭐⭐⭐⭐☆ (4/5) - Good C++ practices  
**Architecture:** ⭐☆☆☆☆ (1/5) - Critical violations  

### **Estimated Grade: 51-60/100**

This represents a **passing but below-average grade** for an advanced programming course. With the critical fixes (separate logic library, remove coupling), the grade could improve to 70-75/100, and with additional improvements, potentially reach 80-85/100.

The student should focus on:
1. Understanding architectural separation principles
2. Proper implementation of design patterns, not just their presence
3. Managing dependencies and coupling
4. Cohesion and single responsibility principle

**Recommendation:** Revise architecture before final submission to improve grade significantly.

---

## Appendix: Review Methodology

This review was conducted by:
1. Analyzing all source files in the repository (~4,352 lines)
2. Examining CMake configuration
3. Evaluating design pattern implementations
4. Assessing coupling and cohesion
5. Checking against project requirements
6. Comparing with industry best practices

**Review Limitations:**
- Could not build and run the project (SFML not available in review environment)
- Could not verify runtime behavior
- Could not check memory leaks with valgrind
- Could not evaluate defense video (not provided)
- Could not assess visual quality and animations

This review focuses on **static code analysis** and **architectural evaluation** based on the provided assignment requirements.

---

**End of Report**
