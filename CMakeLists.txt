cmake_minimum_required(VERSION 3.16)
project(packman)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Vind SFML (minimaal versie 2.6)
find_package(SFML 2.6 COMPONENTS system window graphics)

# Voeg je broncode toe
add_executable(packman main.cpp
        code/game.cpp
        code/logic/state_maneger/stateManeger.cpp
        code/camera.cpp
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
        code/observer.cpp
        code/observer.h
        code/view/entityView.cpp
        code/view/entityView.h
        code/view/notifications.h
        code/view/worldView.cpp
        code/view/worldView.h
        code/view/movableEntityView.cpp
        code/view/movableEntityView.h
        code/view/collectableView.cpp
        code/view/collectableView.h
        code/logic/entities/Ghost.cpp
        code/logic/entities/Ghost.h
        code/view/ghostView.cpp
        code/view/ghostView.h
        code/logic/random.h
        code/logic/random.cpp
        code/logic/entities/Score.cpp
        code/logic/entities/Score.h
        code/view/ScoreView.cpp
        code/view/ScoreView.h
        code/logic/state_maneger/state.cpp
        code/logic/state_maneger/state.h
        code/logic/state_maneger/make_text.h
        code/logic/state_maneger/make_text.cpp
        code/logic/entities/manhattenGhost.cpp
        code/logic/entities/manhattenGhost.h)

include_directories(${SFML_INDCLUDE_DIR})

# Link de SFML-libraries
target_link_libraries(packman sfml-graphics sfml-window sfml-system)