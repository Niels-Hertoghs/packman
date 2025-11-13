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
        code/world.cpp
        code/world.h
        code/logic/entities/entity.cpp
        code/logic/entities/entity.h
        code/render/render.cpp
        code/render/render.h
        code/logic/entities/movableEntity.cpp
        code/logic/entities/movableEntity.h
        code/logic/entities/collectable.cpp
        code/logic/entities/collectable.h
        code/Stopwatch.cpp
        code/Stopwatch.h
        code/observer.cpp
        code/observer.h
        code/render/entityView.cpp
        code/render/entityView.h
        code/render/notifications.h
        code/render/worldView.cpp
        code/render/worldView.h)

include_directories(${SFML_INDCLUDE_DIR})

# Link de SFML-libraries
target_link_libraries(packman sfml-graphics sfml-window sfml-system)