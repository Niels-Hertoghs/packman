cmake_minimum_required(VERSION 3.16)
project(packman)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Vind SFML (minimaal versie 2.6)
find_package(SFML 2.6 COMPONENTS system window graphics)

# --- Logic library ---
add_library(packman_logic
        code/logic/world.cpp
        code/logic/entities/entity.cpp
        code/logic/entities/movableEntity.cpp
        code/logic/entities/collectable.cpp
        code/logic/Stopwatch.cpp
        code/logic/Observer.cpp
        code/logic/entities/Ghost.cpp
        code/logic/random.cpp
        code/logic/Score.cpp
        code/logic/entities/manhattanGhost.cpp
        code/logic/LogicFactory.cpp
)

target_include_directories(packman_logic PUBLIC code/logic)
# If the logic library uses SFML, link it too:
target_link_libraries(packman_logic PUBLIC sfml-system)

# --- Executable ---
add_executable(packman
        main.cpp
        code/view/game.cpp
        code/view/state_maneger/stateManeger.cpp
        code/view/camera.cpp
        code/view/entities/entityView.cpp
        code/view/entities/movableEntityView.cpp
        code/view/entities/collectableView.cpp
        code/view/entities/ghostView.cpp
        code/view/worldView.cpp
        code/view/ScoreView.cpp
        code/view/state_maneger/state.cpp
        code/view/state_maneger/make_text.cpp
        code/view/ViewFactory.cpp
)

target_include_directories(packman PRIVATE code/view)
# Link the logic library and SFML
target_link_libraries(packman PRIVATE packman_logic sfml-graphics sfml-window sfml-system)

# Install the executable in /usr/local/bin
install(TARGETS packman DESTINATION bin)
