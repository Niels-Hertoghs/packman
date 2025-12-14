cmake_minimum_required(VERSION 3.16)
project(packman)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Vind SFML (minimaal versie 2.6)
find_package(SFML 2.6 COMPONENTS system window graphics)

# Verzamel alle source- en headerfiles in code/
file(GLOB_RECURSE PACKMAN_SOURCES
        code/*.cpp
        code/*.h
)

add_executable(packman
        main.cpp
        ${PACKMAN_SOURCES}
)

include_directories(${SFML_INCLUDE_DIR})

# Link de SFML-libraries
target_link_libraries(packman sfml-graphics sfml-window sfml-system)

# Install the executable in /usr/local/bin
install(TARGETS packman DESTINATION bin)