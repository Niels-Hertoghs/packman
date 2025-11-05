cmake_minimum_required(VERSION 3.16)
project(packman)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Vind SFML (minimaal versie 2.5)
find_package(SFML 2 COMPONENTS system window graphics)

# Voeg je broncode toe
add_executable(packman main.cpp
        logic/game.cpp
        logic/state_maneger/stateManeger.cpp
        logic/camera.cpp
        logic/world.cpp
        logic/world.h
        logic/entities/entity.cpp
        logic/entities/entity.h
        logic/render.cpp
        logic/render.h)

include_directories(${SFML_INDCLUDE_DIR})

# Link de SFML-libraries
target_link_libraries(packman sfml-graphics sfml-window sfml-system)