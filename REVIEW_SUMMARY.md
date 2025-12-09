# Code Review Summary - Packman Project

## Quick Reference Guide

**Student:** Niels Hertoghs  
**Project:** Pac-Man Game in C++ with SFML  
**Review Date:** December 9, 2025  

---

## Final Grade: 62/100

### Grade Breakdown
- **Core Game Requirements (40%)**: 25/40
- **Design & Code Quality (40%)**: 29/40  
- **Project Defense (10%)**: 7/10 (estimated)
- **Documentation (10%)**: 0/10 (missing report)
- **Bonus Points (+10%)**: 0/10

---

## Critical Issues ⚠️

### 🔴 MUST FIX (Failing Requirements):

1. **Missing Abstract Factory Pattern** (-5%)
   - Required by assignment, completely absent
   - Entities created directly with `std::make_shared`
   - No factory interface in logic library
   - Fix: Create AbstractFactory interface in logic, ConcreteFactory in view

2. **No Separate Logic Library** (-5%)
   - All code compiled into single executable
   - Requirement: "encapsulate game logic into standalone library"
   - Fix: Restructure CMakeLists.txt with `add_library(logic_lib ...)`

3. **Logic-View Coupling** (-3%)
   - Logic classes include view headers
   - `movableEntity.h` includes `movableEntityView.h`
   - `Score.h` references `view::stateManeger`
   - Fix: Use interfaces, remove direct dependencies

4. **Missing Project Report** (-10%)
   - No documentation of design decisions
   - Required component worth 10% of grade

---

## What Works Well ✅

### Excellent Implementations:
- **Smart Pointers**: Excellent use throughout (10/10)
- **Stopwatch**: Perfect C++ chrono implementation (10/10)
- **Random**: Mersenne Twister properly used (10/10)
- **Camera**: Manual projection as required (10/10)
- **Observer Pattern**: Well implemented (9/10)
- **State Pattern**: Good state machine with stack (8/10)

### Good Code Quality:
- Modern C++ features used correctly
- Virtual destructors present
- Const correctness mostly good
- Exception handling in place
- Clear namespace separation
- No raw pointers (except where appropriate)

---

## Design Patterns Score

| Pattern | Required | Status | Score | Notes |
|---------|----------|--------|-------|-------|
| Observer | ✓ | ✓ | 9/10 | Well implemented |
| State | ✓ | ✓ | 8/10 | Good state stack |
| Singleton | ✓ | ✓ | 4/5 | Works, minor issues |
| Abstract Factory | ✓ | ✗ | 0/10 | **MISSING** |
| MVC | ✓ | ~ | 3/5 | Poor separation |

**Total: 24/45** (should be minimum 35/45 to pass this section)

---

## Cohesion & Coupling Analysis

### Cohesion: 7/10
- ✅ Utility classes have single responsibilities
- ✅ Most entities are well-focused
- ⚠️ World class does too much
- ⚠️ Game class is monolithic

### Coupling: 4/10
- ❌ Logic tightly coupled to view
- ❌ Backward dependencies (logic → view)
- ❌ Cannot compile logic without SFML
- ✅ Good entity hierarchy
- ✅ Independent utility classes

### SOLID Principles: 6.2/10
- **S**ingle Responsibility: 6/10
- **O**pen/Closed: 7/10
- **L**iskov Substitution: 8/10
- **I**nterface Segregation: 7/10
- **D**ependency Inversion: 3/10 ⚠️

---

## Top 5 Priority Fixes

### 1. Implement Abstract Factory (CRITICAL)
**Time:** 2-3 hours  
**Impact:** +5-7 points

```cpp
// logic/AbstractFactory.h
namespace logic {
    class AbstractFactory {
    public:
        virtual std::shared_ptr<entity> createWall(...) = 0;
        virtual std::shared_ptr<movableEntity> createPacman(...) = 0;
        // ... other create methods
    };
}

// view/ConcreteFactory.h
namespace view {
    class ConcreteFactory : public logic::AbstractFactory {
        // Implements factory, attaches views
    };
}
```

### 2. Separate Logic Library (CRITICAL)
**Time:** 1 hour  
**Impact:** +5 points

```cmake
# CMakeLists.txt
add_library(logic_lib STATIC
    code/logic/world.cpp
    code/logic/entities/entity.cpp
    # ... all logic files, NO view files
)

add_executable(packman
    main.cpp
    code/game.cpp
    # ... view files
)

target_link_libraries(packman PRIVATE logic_lib sfml-graphics ...)
# Note: logic_lib should NOT link SFML
```

### 3. Break Logic-View Dependencies (CRITICAL)
**Time:** 2-3 hours  
**Impact:** +3-5 points

- Remove view includes from logic headers
- Use interfaces instead of concrete view types
- Make Score independent of StateManager

### 4. Write Project Report (REQUIRED)
**Time:** 2-3 hours  
**Impact:** +8-10 points

Include:
- Design decisions and rationale
- Class diagram showing separation
- Pattern usage explanation
- Known issues and future work

### 5. Fix Naming Consistency (MINOR)
**Time:** 30 minutes  
**Impact:** +1 point

- `stateManeger` → `stateManager` (everywhere)
- Consistent capitalization
- English naming if required

---

## Code Examples

### ❌ Current (Wrong):
```cpp
// In world.cpp
case '#':
    walls.push_back(std::make_shared<wall>(x, y));  // Direct creation
    break;
```

### ✅ Should Be (Right):
```cpp
// In world.cpp - using factory
case '#':
    auto w = factory->createWall(x, y);  // Factory handles view attachment
    walls.push_back(w);
    break;
```

### ❌ Current (Wrong):
```cpp
// In movableEntity.h (LOGIC!)
#include "../../view/entities/movableEntityView.h"  // Logic includes view!
std::shared_ptr<view::movableEntityView> observer;
```

### ✅ Should Be (Right):
```cpp
// In movableEntity.h (LOGIC)
// No view includes!
std::vector<std::shared_ptr<logic::IEntityObserver>> observers;  // Interface
```

---

## Effort vs Impact Matrix

### High Impact, Low Effort (DO FIRST):
- ✅ Separate logic library (1 hour, +5 points)
- ✅ Write report (2-3 hours, +10 points)

### High Impact, Medium Effort:
- ✅ Abstract Factory (2-3 hours, +5-7 points)
- ✅ Break logic-view coupling (2-3 hours, +3-5 points)

### Low Impact, Low Effort:
- ⭕ Fix naming (30 min, +1 point)
- ⭕ Add comments (1 hour, +1 point)

### Low Impact, High Effort:
- ⭕ Unit tests (4+ hours, +2 points)
- ⭕ Performance optimization (varies, +1 point)

---

## Grade Potential

| Scenario | Grade | Required Changes |
|----------|-------|------------------|
| **Current** | 62/100 | None - failing |
| **With 4 fixes** | 75-80/100 | Factory + Library + Coupling + Report |
| **Perfect** | 85-90/100 | Above + Tests + Polish + Bonus |

---

## Strengths to Maintain

1. ✅ **Smart Pointer Usage** - Excellent, keep this quality
2. ✅ **Modern C++** - Great use of C++17 features
3. ✅ **Utility Classes** - Stopwatch, Random, Camera are exemplary
4. ✅ **Observer Pattern** - Well implemented, good foundation
5. ✅ **State Pattern** - Solid state machine architecture
6. ✅ **Code Organization** - Good file structure and naming (except typo)

---

## Key Takeaways

### What the reviewer is looking for:
1. **Architectural separation** - Can logic exist without view?
2. **Design patterns** - Are required patterns present and correct?
3. **Code quality** - Modern C++, smart pointers, RAII?
4. **Extensibility** - Can new features be added easily?
5. **Documentation** - Is the design explained and justified?

### Why the grade is lower:
- Not about code quality (code is good!)
- Not about features (gameplay works!)
- **About architecture** - Requirements explicitly stated, not met
- Missing mandatory patterns and structure

### How to improve:
- Focus on architectural requirements first
- Factory pattern is not optional - it's required
- Library separation is not optional - it's required  
- Document your work - worth 10% of grade

---

## Next Steps

### Immediate Actions (This Week):
1. Read this review thoroughly
2. Implement Abstract Factory pattern
3. Separate logic into CMake library
4. Remove view dependencies from logic
5. Write 2-page project report

### Validation:
- Can logic compile without SFML? (Should be YES)
- Is AbstractFactory interface present? (Should be YES)
- Can a different view be created without changing logic? (Should be YES)

### Final Check:
- [ ] Logic compiles as separate library
- [ ] Abstract Factory implemented
- [ ] No view includes in logic code
- [ ] Project report written
- [ ] Code compiles and runs
- [ ] CI build passes

---

## Resources

### Recommended Reading:
1. Head First Design Patterns - Chapter on Abstract Factory
2. SFML Game Development book - Chapter on Entity Systems
3. Project assignment section 3.1.1 - Design Patterns requirements

### Example Abstract Factory:
See CODE_REVIEW_REPORT.md Section 7.1 for detailed implementation example

### CMake Library Setup:
See CODE_REVIEW_REPORT.md Section 7.1 for CMakeLists.txt example

---

## Questions to Ask Yourself

1. ❓ Can I compile my logic code without SFML installed? (Should be YES)
2. ❓ Can I create a text-based representation without changing logic? (Should be YES)
3. ❓ Where in my code is the Abstract Factory? (Should have clear answer)
4. ❓ Does my logic depend on my view, or vice versa? (Should be: View depends on Logic)
5. ❓ Have I documented why I made these design choices? (Should be YES)

---

## Final Note

This is **good work** that needs **architectural corrections**. The code quality and features are solid. The issue is that explicit requirements (Abstract Factory, library separation) were not met. With focused effort on the critical issues, this can easily become a 75-80% project.

**The foundation is there - the architecture just needs alignment with requirements.**

---

*For detailed analysis, see CODE_REVIEW_REPORT.md*  
*Review Date: December 9, 2025*
