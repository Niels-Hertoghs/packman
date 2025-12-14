cmake_minimum_required(VERSION 3.16)
project(packman)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Vind SFML (minimaal versie 2.6)
find_package(SFML 2.6 COMPONENTS system window graphics)

# Voeg je broncode toe
add_executable(packman main.cpp
        code/game.cpp
        code/view/state_maneger/stateManeger.cpp
        code/view/camera.cpp
        code/logic/world.cpp
        code/logic/world.h
        code/logic/entities/entity.cpp
        code/logic/entities/entity.h
        code/logic/entities/movableEntity.cpp
        code/logic/entities/movableEntity.h
        code/logic/entities/collectable.cpp
        code/logic/entities/collectable.h
        code/logic/Stopwatch.cpp
        code/logic/Stopwatch.h
        code/observerView.cpp
        code/observerView.h
        code/view/entities/entityView.cpp
        code/view/entities/entityView.h
        code/view/notifications.h
        code/view/worldView.cpp
        code/view/worldView.h
        code/view/entities/movableEntityView.cpp
        code/view/entities/movableEntityView.h
        code/view/entities/collectableView.cpp
        code/view/entities/collectableView.h
        code/logic/entities/Ghost.cpp
        code/logic/entities/Ghost.h
        code/view/entities/ghostView.cpp
        code/view/entities/ghostView.h
        code/logic/random.h
        code/logic/random.cpp
        code/logic/Score.cpp
        code/logic/Score.h
        code/view/ScoreView.cpp
        code/view/ScoreView.h
        code/view/state_maneger/state.cpp
        code/view/state_maneger/state.h
        code/view/state_maneger/make_text.h
        code/view/state_maneger/make_text.cpp
        code/logic/entities/manhattanGhost.cpp
        code/logic/entities/manhattanGhost.h
        code/BaseFactory.h
        code/view/ViewFactory.h
        code/view/ViewFactory.cpp
        code/logic/LogicFactory.h
        code/logic/LogicFactory.cpp
        code/logic/Observer.cpp
        code/logic/Observer.h
        code/view/observerView.cpp
        code/view/observerView.h)

include_directories(${SFML_INCLUDE_DIR})

# Link de SFML-libraries
target_link_libraries(packman sfml-graphics sfml-window sfml-system)

# Install the executable in /usr/local/bin
install(TARGETS packman DESTINATION bin)