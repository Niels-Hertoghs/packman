cmake_minimum_required(VERSION 3.16)
project(packman)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Vind SFML (minimaal versie 2.5)
find_package(SFML 2 COMPONENTS system window graphics)

# Voeg je broncode toe
add_executable(packman main.cpp
        logic/game.cpp
        logic/game.h
        logic/state_maneger/stateManeger.cpp
        logic/state_maneger/stateManeger.h)

include_directories(${SFML_INDCLUDE_DIR})

# Link de SFML-libraries
target_link_libraries(packman sfml-graphics sfml-window sfml-system)