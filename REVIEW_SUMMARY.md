# Code Review Summary - Packman Project

## Quick Reference

**Date:** December 15, 2025  
**Estimated Grade:** 46/100 (FAIL)  
**Status:** Requires major revisions to pass

---

## Critical Issues (Must Fix to Pass)

### 1. ❌ No Separate Logic Library (-15%)
**Problem:** All code compiled into single executable. Logic not separated from SFML.

**Current CMakeLists.txt:**
```cmake
add_executable(packman
    main.cpp
    ${PACKMAN_SOURCES}  # Everything mixed together
)
```

**Required Fix:**
```cmake
# Create separate logic library
add_library(packman_logic STATIC
    code/logic/world.cpp
    code/logic/entities/*.cpp
    code/logic/Score.cpp
    code/logic/Stopwatch.cpp
    code/logic/random.cpp
    code/logic/Observer.cpp
    code/logic/LogicFactory.cpp
)

# Logic should NOT link SFML
target_include_directories(packman_logic PUBLIC code/logic)

# Executable only contains view/main
add_executable(packman
    main.cpp
    code/game.cpp
    code/view/*.cpp
    code/BaseFactory.cpp
)

target_link_libraries(packman packman_logic sfml-graphics sfml-window sfml-system)
```

**Impact:** Cannot build logic without SFML installed. Violates core requirement.

---

### 2. ❌ Logic Depends on View (-10%)
**Problem:** Score class includes view headers and manipulates UI state.

**Evidence:**
```cpp
// In code/logic/Score.h (LOGIC LAYER)
#include "../view/ScoreView.h"               // WRONG!
#include "../view/state_maneger/stateManeger.h"  // WRONG!

// In Score.cpp
manager.prevState();
manager.pushState(std::move(state));  // Logic controlling View!
```

**Required Fix:**
```cpp
// Score should emit events, not control UI
class Score : public Observer<scoreNotifications> {
    std::vector<std::shared_ptr<ScoreObserver>> observers;
    
    void notifyGameOver() {
        for (auto& obs : observers) {
            obs->onGameOver(score);  // Let view handle state
        }
    }
};
```

**Impact:** Cannot separate representations. Breaks MVC pattern.

---

### 3. ❌ Score Persistence Missing (-5%)
**Problem:** High scores not saved to file. Top 5 scores not maintained.

**Required Features:**
- Save top 5 scores to file
- Load scores on game start
- Display on menu screen
- Update when player achieves high score

**Implementation Needed:**
```cpp
class Score {
    std::vector<int> topScores;  // Top 5 scores
    
    void loadHighScores(const std::string& filename);
    void saveHighScores(const std::string& filename);
    bool isHighScore(int score) const;
    void addHighScore(int score);
    std::vector<int> getTopFive() const;
};
```

---

### 4. ❌ Abstract Factory Misused (-5%)
**Problem:** World creates concrete factory locally. Factory not injected by Game.

**Current (Wrong):**
```cpp
// In world.cpp
void world::startWorld(int level) {
    std::unique_ptr<ConcreteLogicFactory> factory = 
        std::make_unique<ConcreteLogicFactory>();  // Direct instantiation!
    // ...
}
```

**Required (Correct):**
```cpp
// Factory should be injected
class world {
    std::shared_ptr<AbstractFactory> factory;
public:
    world(std::shared_ptr<AbstractFactory> factory) 
        : factory(factory) {}
};

// In game.cpp
auto concreteFactory = std::make_shared<ConcreteViewFactory>(cam, window);
auto world = std::make_shared<World>(concreteFactory);
```

---

### 5. ❌ Missing Documentation (-8%)
**Required but Missing:**
- [ ] README.md with project overview
- [ ] Build instructions
- [ ] 2-page design report explaining choices
- [ ] 10-minute video (3 min gameplay + 7 min design discussion)

---

## Major Issues (Important to Fix)

### High Coupling
- Logic classes use global Singletons (tight coupling)
- Hardcoded file paths ("input_output/map.txt")
- Concrete type dependencies instead of interfaces

**Fix with Dependency Injection:**
```cpp
class World {
    std::shared_ptr<ITimeProvider> timeProvider;
    std::shared_ptr<IRandomProvider> randomProvider;
    std::shared_ptr<IFileReader> fileReader;
public:
    World(std::shared_ptr<ITimeProvider> time,
          std::shared_ptr<IRandomProvider> random,
          std::shared_ptr<IFileReader> reader);
};
```

### Low Cohesion
**Stopwatch does too much:**
- Tracks time ✓
- Manages sprite animation rate ✗
- Handles fear mode duration ✗  
- Controls ghost spawn timing ✗

**Should be split:**
- TimeKeeper: Basic time tracking
- AnimationTimer: Sprite changes
- GameTimer: Game-specific timing

**World does too many things:**
- Entity creation (should be factory)
- Update logic (should be separate system)
- Collision detection (should be separate system)
- Event notification (should be separate system)

### Inconsistent Code Style
- Mixed English/Dutch (comments, variables)
- Inconsistent naming: `get_walls()` vs `getX()`
- Classes: `movableEntity` vs `Pacman`
- `.clang-format` present but not applied

---

## What's Good

### ✅ State Pattern
Well-implemented state machine with stack:
- Clean state hierarchy
- Proper state transitions
- Good use of unique_ptr

### ✅ Ghost AI Hierarchy
Thoughtful class design:
```
Ghost (abstract)
├── redGhost (random)
└── manhattanGhost (abstract)
    ├── frontManhattanGhost
    │   ├── blueGhost
    │   └── greenGhost
    └── orangeGhost (chases back)
```

### ✅ Smart Pointers
- Consistent use throughout
- No manual new/delete
- Proper RAII

### ✅ Singletons
- Thread-safe implementation
- Copy/assignment deleted
- Meyer's Singleton pattern

---

## Path to Passing Grade (50%+)

**Priority fixes to reach 67%:**

1. Create separate logic library (+8%)
2. Fix dependency direction (+5%)
3. Implement score persistence (+3%)
4. Fix Abstract Factory usage (+3%)
5. Write 2-page design report (+3%)

**With these 5 fixes: Passing grade achieved**

---

## Grade Breakdown

| Component | Current | Possible | Notes |
|-----------|---------|----------|-------|
| Core Functionality | 28 | 40 | Most features work |
| Design & Quality | 16 | 40 | Critical issues present |
| Documentation | 2 | 10 | Missing report & video |
| Defense | 0 | 10 | No video found |
| Bonus | 0 | 10 | No extra features |
| **TOTAL** | **46** | **100** | **FAIL** |

---

## Detailed Findings

See **CODE_REVIEW_REPORT.md** for:
- Complete analysis of all 6 required classes
- Detailed design pattern evaluations
- Code quality metrics
- Full gameplay requirements checklist
- Specific code examples and fixes
- Improvement recommendations
- Areas of strength and weakness

---

## Immediate Action Items

**Before next submission:**

1. [ ] Refactor CMakeLists.txt to create separate library
2. [ ] Remove all view includes from logic layer
3. [ ] Implement score persistence to file
4. [ ] Add dependency injection for factories
5. [ ] Write 2-page design report
6. [ ] Record 10-minute defense video
7. [ ] Create README with build instructions
8. [ ] Apply clang-format to entire codebase
9. [ ] Add exception handling for resource loading
10. [ ] Test that logic compiles without SFML

**Testing Checklist:**

```bash
# Logic library should build without SFML
cd build
cmake -DSFML_DIR=/nonexistent ..  # Should still compile logic library
make packman_logic  # Should succeed

# Full build
cmake ..
make packman  # Should succeed

# Run
./packman  # Should launch and run correctly
```

---

## Final Assessment

This project shows **programming ability** but fails to meet **architectural requirements**. The core game logic works, which demonstrates understanding of algorithms and OOP basics. However, the critical missing separate library and backwards dependencies are fundamental violations that prevent passing.

**The foundation is salvageable with focused effort on the critical issues.**

Good luck with the revisions!

