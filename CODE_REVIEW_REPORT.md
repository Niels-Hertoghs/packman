# Advanced Programming Project - Code Review Report
## Pac-Man Game Implementation

**Student:** Niels Hertoghs  
**Date:** December 9, 2025  
**Reviewer:** AI Code Review Assistant  

---

## Executive Summary

This comprehensive code review evaluates the Pac-Man game implementation against the project requirements, focusing on design patterns, code quality, cohesion, coupling, and adherence to best practices. The implementation demonstrates a **solid understanding** of object-oriented programming principles and makes good use of several design patterns. However, there are critical architectural issues that significantly impact the grade.

**Overall Grade Estimate: 62/100**

---

## 1. Technical Requirements Analysis (40%)

### 1.1 Core Functionalities (/40)

#### ✅ Implemented Features:
- **Game Startup & Initialization**: StateManager handles menu state
- **Maze Representation**: Text file-based map loading system
- **Player Controls**: Movement system with continuous motion
- **Ghost Movement and AI**: Four ghosts with different behaviors (red, blue, green, orange)
- **Coin Collection**: Collectable system with scoring
- **Fruits and Ghost Transformation**: Fear mode implementation
- **Multiple Lives**: Lives system with respawn logic
- **Scoring System**: Time-based scoring with level progression

#### ⚠️ Issues Identified:
1. **No Abstract Factory Pattern** (CRITICAL): The most significant missing requirement
   - Entities are directly instantiated in `world.cpp` using `std::make_shared`
   - No factory interface defined in the logic library
   - Views are created directly in worldView.cpp without factory abstraction
   - This violates the core separation of concerns requirement

2. **CMake Structure** (CRITICAL):
   - **No separate logic library** - everything is compiled into a single executable
   - The assignment explicitly requires: *"encapsulate the game logic into a standalone (static or dynamic) library"*
   - Current CMakeLists.txt lists all files in one `add_executable()` command
   - Should have: `add_library(logic_lib STATIC ...)` and `target_link_libraries(packman logic_lib ...)`

3. **MVC Separation Issues**:
   - Logic entities include SFML-specific view references (observer pattern is correct, but coupling is tight)
   - `observer.h` includes `<SFML/Graphics.hpp>` despite being in the root, not view directory
   - Views correctly separated, but the boundary is blurred

**Score: 25/40** - Core gameplay mostly works, but critical architectural requirements are missing

---

## 2. Design Patterns & Code Quality (40%)

### 2.1 Required Design Patterns

#### ✅ Observer Pattern (Good Implementation)
**Grade: 9/10**
```cpp
// Well implemented with proper inheritance
class IObserver { virtual ~IObserver() = default; };
class Observer : public IObserver { /* ... */ };
```
- Properly used for Model-View updates
- Score class correctly observes game events
- Views observe their corresponding models
- **Minor Issue**: Generic IObserver interface is good, but could use type safety

#### ✅ State Pattern (Good Implementation)
**Grade: 8/10**
```cpp
class stateManeger {
    std::stack<std::unique_ptr<view::state>> stack;
};
```
- Proper state stack implementation
- MenuState, LevelState, PausedState, VictoryState, GameOverState all present
- Transitions handled correctly
- **Minor Issue**: Typo in class name "stateManeger" should be "stateManager"

#### ✅ Singleton Pattern (Acceptable Implementation)
**Grade: 7/10**
```cpp
class Stopwatch {
    inline static std::shared_ptr<Stopwatch> _instance;
    static std::shared_ptr<Stopwatch> getInstance();
};
```
- Correctly implemented for Stopwatch and Random classes
- Thread-safe lazy initialization
- **Issues**:
  - Uses `new` in factory method instead of `std::make_shared`
  - Not thread-safe (no mutex protection)
  - Over-reliance on singletons (anti-pattern for testing)

#### ❌ Abstract Factory Pattern (NOT IMPLEMENTED)
**Grade: 0/10**

**CRITICAL FAILURE**: This is explicitly required and completely missing.

**What's missing:**
```cpp
// Required but NOT present:
namespace logic {
    class AbstractFactory {
    public:
        virtual std::shared_ptr<entity> createWall(double x, double y) = 0;
        virtual std::shared_ptr<entity> createPacman(double x, double y) = 0;
        virtual std::shared_ptr<entity> createGhost(...) = 0;
        virtual ~AbstractFactory() = default;
    };
}

// Concrete factory in representation:
namespace view {
    class ConcreteFactory : public logic::AbstractFactory {
        // Creates entities WITH views attached
    };
}
```

**Current implementation:**
- Entities created directly: `walls.push_back(std::make_shared<wall>(x, y));`
- Views created directly: `walls.push_back(std::make_shared<wallView>(...));`
- No factory interface anywhere in the codebase

#### ⚠️ MVC Pattern (Partial Implementation)
**Grade: 6/10**

**Strengths:**
- Clear Model classes (entity, movableEntity, Ghost, Pacman, etc.)
- Separate View classes (entityView, ghostView, pacmanView, etc.)
- World acts as controller

**Weaknesses:**
- Models hold shared_ptr to Views (tight coupling)
- SFML includes leak into logic code through observer.h
- No true separation - cannot compile logic without SFML

### 2.2 Code Quality Analysis

#### ✅ Namespace Usage (Good)
**Grade: 9/10**
```cpp
namespace logic { /* game logic */ }
namespace view { /* representation */ }
```
- Clear modular separation
- Consistent usage throughout

#### ✅ Smart Pointers (Excellent)
**Grade: 10/10**
- Extensive use of `std::shared_ptr` and `std::unique_ptr`
- Correct use of `std::weak_ptr` in views (e.g., `wallView::wallModel`)
- No raw pointers except where necessary (references preferred)
- Memory management is solid

#### ✅ Exception Handling (Good)
**Grade: 8/10**
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
- Present in critical areas (file I/O)
- Could be more comprehensive

#### ✅ Const Correctness (Good)
**Grade: 8/10**
- Good use of `const` in method signatures
- `[[nodiscard]]` attributes used appropriately
- Some missed opportunities (parameters could be const references)

#### ✅ Virtual Destructors (Good)
**Grade: 9/10**
- All base classes have `virtual ~ClassName() = default;`
- Proper use of `override` keyword
- No memory leaks likely

#### ⚠️ Code Comments (Adequate)
**Grade: 6/10**
- Good Doxygen-style documentation in headers
- **Issue**: All comments in Dutch, not English (project requirement unclear)
- Missing inline comments for complex logic
- Good API documentation structure

#### ✅ Stopwatch Implementation (Excellent)
**Grade: 10/10**
```cpp
using clock = std::chrono::high_resolution_clock;
std::chrono::time_point<clock> lastTime;
```
- Uses C++ chrono, not SFML Clock as required
- Proper deltaTime calculation
- Multiple timing functions (animations, fear mode, etc.)

#### ✅ Random Implementation (Excellent)
**Grade: 10/10**
```cpp
std::mt19937 mt;  // Mersenne Twister
random() : mt(std::random_device{}()) {}
```
- Uses Mersenne Twister as suggested
- Not using legacy rand/srand
- Single instance maintained

#### ✅ Camera Implementation (Excellent)
**Grade: 10/10**
```cpp
std::pair<int,int> worldToPixel(const double& x, const double& y) const {
    int pixelX = static_cast<int>(((x + 1.f) / 2.f) * width);
    int pixelY = static_cast<int>(((-y + 1.f) / 2.f) * height);
    return {pixelX, pixelY};
}
```
- Normalized coordinate system [-1, 1] implemented correctly
- Manual projection without SFML utilities
- Resolution-independent logic

#### ⚠️ Dynamic Casts (Not Checked)
**Grade: ?/10**
- Could not verify if dynamic_cast is avoided throughout
- Appears to use polymorphism correctly from visible code

#### ⚠️ Code Duplication (Minor Issues)
**Grade: 7/10**
- Some similar ghost initialization code
- Could benefit from templates or factory methods
- Generally acceptable level of duplication

**Overall Code Quality Score: 29/40**

---

## 3. Design Principles Analysis

### 3.1 Cohesion (How well do classes stick together?)

#### ✅ High Cohesion Examples:
- **Stopwatch**: Single responsibility - time management
- **Camera**: Single responsibility - coordinate transformation  
- **Random**: Single responsibility - random number generation
- **Score**: Focused on score management and level tracking

#### ⚠️ Medium Cohesion:
- **World**: Does multiple things (entity storage, collision detection, game orchestration)
  - Could be split into separate concerns
  - Acceptable for a controller class

#### ❌ Low Cohesion:
- **game class**: Static method that does everything
  - Window creation, event handling, state management all in one method
  - Should be refactored into smaller responsibilities

**Cohesion Grade: 7/10**

### 3.2 Coupling (How dependent are classes on each other?)

#### ❌ High Coupling Issues:

1. **Logic-View Coupling (CRITICAL)**:
```cpp
// In movableEntity.h (LOGIC)
#include "../../view/entities/movableEntityView.h"
std::shared_ptr<view::movableEntityView> observer;
```
- Logic entities directly reference view types
- Cannot compile logic without view headers
- Violates separation requirement

2. **Observer Pattern Coupling**:
```cpp
// In observer.h (root level)
#include <SFML/Graphics.hpp>  // SHOULD NOT BE HERE
```
- Observer base class shouldn't depend on SFML
- Should be in logic library, but includes graphics library

3. **StateManager-Score Coupling**:
```cpp
// Score.h
view::stateManeger& manager;  // Logic depends on view!
```
- Score (logic) holds reference to StateManager (view)
- Backwards dependency - logic should NOT know about view states

4. **Forward Declaration Issues**:
- Excessive use of forward declarations indicates tight coupling
- Many circular dependencies worked around

#### ✅ Good Decoupling:
- Camera is independent
- Stopwatch and Random are independent utilities
- Entity hierarchy is clean

**Coupling Grade: 4/10** - Critical architectural coupling issues

### 3.3 SOLID Principles

#### Single Responsibility Principle (SRP)
**Grade: 6/10**
- ✅ Most utility classes follow SRP well
- ❌ `game::playGame()` violates SRP (does too much)
- ❌ `World` has multiple responsibilities

#### Open/Closed Principle (OCP)
**Grade: 7/10**
- ✅ Good use of inheritance (Ghost hierarchy, State hierarchy)
- ✅ Easy to add new ghost types
- ⚠️ Some modification needed for new features

#### Liskov Substitution Principle (LSP)
**Grade: 8/10**
- ✅ Polymorphic behavior works correctly
- ✅ Derived classes properly substitute base classes

#### Interface Segregation Principle (ISP)
**Grade: 7/10**
- ✅ Interfaces not too large
- ⚠️ Observer interface could be more specific

#### Dependency Inversion Principle (DIP)
**Grade: 3/10** - **CRITICAL FAILURE**
- ❌ High-level logic depends on low-level view implementations
- ❌ No abstractions between logic and view (missing Abstract Factory)
- ❌ Concrete classes depend on concrete classes instead of interfaces

**SOLID Principles Average: 6.2/10**

---

## 4. Critical Issues Summary

### 🔴 CRITICAL (Must Fix):

1. **No Abstract Factory Pattern** - Requirement explicitly stated, completely missing
   - Impact: Cannot switch representations without modifying logic
   - Cannot compile logic library independently
   - Automatic 0 points for this requirement

2. **No Separate Logic Library** - CMakeLists.txt compiles everything together
   - Requirement: Logic must be in standalone library
   - Current: All in one executable
   - Impact: Cannot link different representations
   - Violates core architectural requirement

3. **Logic Depends on View** - Multiple violations of separation
   - `movableEntity.h` includes view headers
   - `Score.h` references `view::stateManeger`
   - `observer.h` includes SFML in what should be logic code
   - Impact: Cannot compile or test logic independently

### 🟡 MAJOR (Should Fix):

4. **High Coupling Between Layers**
   - Forward/backward dependencies everywhere
   - Difficult to test, maintain, or extend

5. **StateManager Naming** - Typo throughout: "stateManeger" → "stateManager"

6. **Game Class Design** - Monolithic static method
   - Should be instance-based
   - Responsibilities should be delegated

### 🟢 MINOR (Nice to Fix):

7. **Comments in Dutch** - May not be an issue if allowed
8. **Some code duplication** - Not severe
9. **Singleton thread safety** - Low priority for single-threaded game

---

## 5. Detailed Grading Breakdown

### 5.1 Core Game Requirements (40%)
| Criterion | Points | Score | Notes |
|-----------|--------|-------|-------|
| Basic Gameplay | 20 | 18 | Most features work |
| Ghost AI | 10 | 9 | Good implementation |
| Scoring System | 5 | 5 | Excellent |
| Level Progression | 5 | 4 | Works, minor issues |
| **Subtotal** | **40** | **36** | |

**Penalty: -11 points for missing Abstract Factory and library separation**

**Final Core Requirements: 25/40**

### 5.2 Design & Code Quality (40%)
| Criterion | Points | Score | Notes |
|-----------|--------|-------|-------|
| Observer Pattern | 10 | 9 | Good |
| State Pattern | 10 | 8 | Good |
| Singleton Pattern | 5 | 4 | Acceptable |
| Abstract Factory | 10 | 0 | **MISSING** |
| MVC Separation | 5 | 3 | Poor separation |
| Smart Pointers | 5 | 5 | Excellent |
| Code Quality | 5 | 4 | Good overall |
| **Subtotal** | **50** | **33** | Capped at 40 |

**Final Design & Quality: 29/40**

### 5.3 Project Defense (10%)
*Cannot evaluate - requires video*

**Estimated: 7/10** (based on code quality)

### 5.4 Documentation (10%)
*No report found - only code*

**Estimated: 0/10** (missing project report)

### 5.5 Bonus Points (10%)
*Cannot fully evaluate without running*

**Estimated: 0/10** (no evident extensions)

---

## 6. Strengths of the Implementation

1. **Excellent use of modern C++ features**:
   - Smart pointers used correctly throughout
   - C++17 features utilized
   - RAII principles followed

2. **Good class hierarchy design**:
   - Clean entity inheritance structure
   - Proper use of abstract classes
   - Virtual destructors everywhere

3. **Solid utility classes**:
   - Stopwatch implementation is exemplary
   - Random class uses proper C++ random
   - Camera projection done manually as required

4. **State pattern implementation**:
   - State stack architecture is well done
   - Easy to add new states
   - Proper state transitions

5. **Observer pattern for Model-View updates**:
   - Decouples update notifications
   - Proper use of weak_ptr to avoid circular references

6. **Comprehensive feature set**:
   - All gameplay features appear to be implemented
   - Ghost AI with different behaviors
   - Time-based scoring system

---

## 7. Areas for Improvement

### 7.1 Architecture (CRITICAL)

**Must Implement:**

```cmake
# CMakeLists.txt should have:
add_library(logic_lib STATIC
    code/logic/world.cpp
    code/logic/entities/entity.cpp
    # ... all logic files
)

target_include_directories(logic_lib PUBLIC code/logic)
# DO NOT link SFML to logic_lib

add_executable(packman
    main.cpp
    code/game.cpp
    # ... all view files
)

target_link_libraries(packman 
    PRIVATE logic_lib 
    PRIVATE sfml-graphics sfml-window sfml-system
)
```

**Must Create Abstract Factory:**

```cpp
// In logic library: AbstractFactory.h
namespace logic {
    class AbstractFactory {
    public:
        virtual std::shared_ptr<entity> createWall(double x, double y) = 0;
        virtual std::shared_ptr<movableEntity> createPacman(double x, double y, double speed) = 0;
        virtual std::shared_ptr<Ghost> createGhost(GhostType type, double x, double y, double speed) = 0;
        virtual std::shared_ptr<collectable> createCollectable(CollectableType type, double x, double y) = 0;
        virtual ~AbstractFactory() = default;
    };
}

// In view code: ConcreteFactory.h
namespace view {
    class ConcreteFactory : public logic::AbstractFactory {
        sf::RenderWindow& window;
        camera& cam;
    public:
        ConcreteFactory(sf::RenderWindow& w, camera& c) : window(w), cam(c) {}
        
        std::shared_ptr<entity> createWall(double x, double y) override {
            auto wall = std::make_shared<logic::wall>(x, y);
            auto wallV = std::make_shared<wallView>(window, cam, wall);
            // Attach observer here
            return wall;
        }
        // ... implement other create methods
    };
}
```

### 7.2 Decouple Logic from View

**Issue:** Logic entities directly include and store view types.

**Solution:**
```cpp
// Remove from movableEntity.h:
// #include "../../view/entities/movableEntityView.h"
// std::shared_ptr<view::movableEntityView> observer;

// Instead, use generic observer from logic:
namespace logic {
    class IEntityObserver {
    public:
        virtual void onPositionChanged() = 0;
        virtual void onDirectionChanged() = 0;
        virtual ~IEntityObserver() = default;
    };
}

// In movableEntity:
std::vector<std::shared_ptr<logic::IEntityObserver>> observers;
```

### 7.3 Fix Score-StateManager Coupling

**Issue:** Score (logic) references StateManager (view).

**Solution:** Use callback/event system:
```cpp
// In Score.h - remove direct reference to stateManeger
// Instead:
namespace logic {
    class IGameStateListener {
    public:
        virtual void onGameOver() = 0;
        virtual void onLevelComplete() = 0;
        virtual ~IGameStateListener() = default;
    };
    
    class Score : public IObserver {
        std::shared_ptr<IGameStateListener> stateListener;
    public:
        void setStateListener(std::shared_ptr<IGameStateListener> listener) {
            stateListener = listener;
        }
        
        void liveLost() {
            livesLeft--;
            if (livesLeft < 0 && stateListener) {
                stateListener->onGameOver();
            }
        }
    };
}

// StateManager implements IGameStateListener
```

### 7.4 Refactor Game Class

**Issue:** Monolithic static method doing everything.

**Solution:**
```cpp
class Game {
    std::unique_ptr<sf::RenderWindow> window;
    view::camera camera;
    view::stateManeger stateManager;
    std::shared_ptr<logic::world> world;
    
public:
    Game();
    void initialize();
    void run();  // Main game loop
    
private:
    void handleEvents();
    void update(float deltaTime);
    void render();
};
```

### 7.5 Improve Naming Consistency

1. Class names: Standardize capitalization (Pacman vs Ghost vs stateManeger)
2. Fix typo: `stateManeger` → `stateManager`
3. Consider English naming convention for international projects

### 7.6 Add Unit Tests

**Missing:** No test infrastructure visible.

**Recommendation:**
- Add Google Test or Catch2
- Test logic independently (easy once separated from view)
- Test game mechanics, AI, scoring

### 7.7 Documentation

**Missing:** Project report (required 10% of grade).

**Should Include:**
- Design decisions and rationale
- Class diagram
- Explanation of pattern usage
- Gameplay instructions
- Build instructions

---

## 8. Code Examples - Good vs. Needs Improvement

### ✅ GOOD Example: Stopwatch Implementation
```cpp
// Excellent use of C++ chrono
void Stopwatch::tick() {
    const auto currentTime = clock::now();
    const std::chrono::duration<float> elapsed = currentTime - lastTime;
    deltaTime = elapsed.count();
    lastTime = currentTime;
}
```
**Why good:** Uses modern C++, const correctness, clear variable names, simple logic.

### ✅ GOOD Example: Smart Pointer Usage
```cpp
// In worldView - proper weak_ptr to avoid circular reference
std::weak_ptr<logic::wall> wallModel;
```
**Why good:** Prevents memory leaks from circular dependencies.

### ❌ NEEDS IMPROVEMENT: Direct Entity Creation
```cpp
// In world.cpp startWorld() - violates Abstract Factory requirement
case '#':
    walls.push_back(std::make_shared<wall>(x, y));
    break;
case 'p':
    pacman = std::make_shared<Pacman>(x + 1.f/20.f, y - 1.f/14.f, 1.f);
    break;
```
**Why bad:** Should use factory->createWall(), factory->createPacman().

### ❌ NEEDS IMPROVEMENT: Logic-View Coupling
```cpp
// In movableEntity.h (logic layer!)
#include "../../view/entities/movableEntityView.h"
std::shared_ptr<view::movableEntityView> observer;
```
**Why bad:** Logic should not know about view types. Use interface.

### ❌ NEEDS IMPROVEMENT: Backwards Dependency
```cpp
// In Score.h (logic layer!)
#include "../view/state_maneger/stateManeger.h"
view::stateManeger& manager;
```
**Why bad:** Logic depending on view violates layered architecture.

---

## 9. Testing & Validation

### Cannot Verify (No Build Environment):
- Actual gameplay functionality
- Ghost AI behavior correctness
- Collision detection accuracy
- Performance
- Memory leaks (though structure looks good)

### Can Verify from Code:
- ✅ Design patterns (partial)
- ✅ Code structure
- ✅ Smart pointer usage
- ✅ Naming conventions
- ❌ Library separation (clearly violated)
- ❌ Abstract Factory (clearly missing)

---

## 10. Recommendations for Improvement

### Priority 1 (CRITICAL - Required to Pass):
1. **Implement Abstract Factory Pattern** - 2-3 hours work
2. **Separate Logic into Library** - 1 hour CMake work
3. **Break Logic-View Dependencies** - 2-3 hours refactoring
4. **Write Project Report** - 2-3 hours documentation

### Priority 2 (MAJOR - Significantly Improve Grade):
5. **Decouple Score from StateManager** - 1 hour refactoring
6. **Refactor Game class** - 1-2 hours
7. **Fix naming consistency** - 30 minutes

### Priority 3 (MINOR - Polish):
8. **Add unit tests** - 3-4 hours
9. **Improve inline documentation** - 1 hour
10. **Add .clang-format compliance** - 30 minutes

---

## 11. Final Grade Calculation

### Scoring Summary:
| Category | Weight | Score | Weighted |
|----------|--------|-------|----------|
| Core Game Requirements | 40% | 25/40 | 10.0 |
| Design & Code Quality | 40% | 29/40 | 11.6 |
| Project Defense | 10% | 7/10 | 0.7 |
| Documentation | 10% | 0/10 | 0.0 |
| Bonus Points | +10% | 0/10 | 0.0 |
| **TOTAL** | **100%** | | **22.3/30** |

### Scaling to Percentage:
- Raw Score: 22.3/30 = 74.3%
- **Critical Penalties Applied:**
  - Missing Abstract Factory: -5%
  - No Library Separation: -5%
  - Logic-View Coupling: -3%
  
**Final Grade: 61.3% ≈ 62/100**

---

## 12. Comparison to Requirements

| Requirement | Required | Status | Impact |
|-------------|----------|--------|--------|
| Separate Logic Library | ✓ | ✗ Missing | -5% |
| Abstract Factory | ✓ | ✗ Missing | -5% |
| Observer Pattern | ✓ | ✓ Implemented | +4% |
| State Pattern | ✓ | ✓ Implemented | +4% |
| Singleton Pattern | ✓ | ✓ Implemented | +2% |
| MVC Separation | ✓ | ~ Partial | -3% |
| Smart Pointers | ✓ | ✓ Excellent | +5% |
| Stopwatch (C++) | ✓ | ✓ Excellent | +5% |
| Random (Mersenne) | ✓ | ✓ Excellent | +5% |
| Camera (Manual) | ✓ | ✓ Excellent | +5% |
| Exception Handling | ✓ | ✓ Present | +3% |
| Namespaces | ✓ | ✓ Used | +3% |
| Virtual Destructors | ✓ | ✓ Present | +3% |
| Const Correctness | ✓ | ✓ Good | +3% |
| Documentation | ✓ | ~ Partial | -5% |

---

## 13. Conclusion

This Pac-Man implementation demonstrates **strong programming skills** and a **good grasp of object-oriented design**. The code is generally well-written, makes excellent use of modern C++ features, and implements most gameplay requirements successfully.

However, the project has **two critical architectural failures** that cannot be overlooked:

1. **Missing Abstract Factory Pattern** - This was explicitly required and is completely absent
2. **No Separate Logic Library** - Logic and view are compiled together, violating the core separation requirement

These issues fundamentally compromise the architecture and prevent the code from meeting the stated requirements for a flexible, extendable design. The logic cannot be compiled independently, and alternative representations cannot be created without modifying logic code.

### Student Strengths:
- ✅ Excellent use of smart pointers
- ✅ Good implementation of Observer and State patterns
- ✅ Strong understanding of C++ features
- ✅ Clean code style and organization
- ✅ Comprehensive feature implementation

### Critical Gaps:
- ❌ Abstract Factory completely missing
- ❌ Logic not separated into library
- ❌ Logic-View coupling throughout
- ❌ Missing project report
- ❌ Backward dependencies (logic → view)

### Path to Higher Grade:
With 4-6 hours of focused refactoring to address the critical issues, this project could easily achieve 75-80%. The foundation is solid; the architecture just needs to be corrected to match requirements.

---

## 14. Grading Rubric Applied

### Actual Grade Distribution:

**Core Game Requirements: 25/40**
- Gameplay: 18/20 ✓
- Design Requirements: 7/20 ✗ (Missing factory + library)

**Design & Code Quality: 29/40**
- Observer: 9/10 ✓
- State: 8/10 ✓  
- Singleton: 4/5 ✓
- Abstract Factory: 0/10 ✗
- MVC: 3/5 ~
- Code Quality: 5/10 ✓

**Project Defense: 7/10** (estimated)
**Documentation: 0/10** (no report)
**Bonus: 0/10** (no extensions evident)

---

## Final Recommendation

**Grade: 62/100 (Passing, but needs significant improvement)**

The student clearly has the skills to achieve a much higher grade. The critical issues are fixable with focused effort on:
1. Creating an AbstractFactory interface and implementation
2. Restructuring CMakeLists.txt to separate logic library
3. Removing view dependencies from logic code
4. Writing the project report

**This is good work that falls short of requirements due to architectural oversights, not lack of ability.**

---

*Report Generated: December 9, 2025*
*Code Reviewed: Packman Project by Niels Hertoghs*
*Review Method: Static code analysis without compilation/execution*
