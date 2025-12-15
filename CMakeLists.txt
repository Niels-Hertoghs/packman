
cmake_minimum_required(VERSION 3.16)
project(packman)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Zoek SFML
find_package(SFML 2.6 COMPONENTS system window graphics)

# =========================
# LOGIC LIBRARY
# =========================
file(GLOB_RECURSE LOGIC_SOURCES
        code/logic/*.cpp
        code/logic/*.h
)

add_library(packman_logic STATIC
        ${LOGIC_SOURCES}
)

target_include_directories(packman_logic PUBLIC
        code/logic
)

# =========================
# EXECUTABLE (VIEW + MAIN)
# =========================
file(GLOB_RECURSE VIEW_SOURCES
        code/view/*.cpp
        code/view/*.h
)

add_executable(packman
        main.cpp
        ${VIEW_SOURCES}
)

target_include_directories(packman PRIVATE
        code/view
)

# Link logic library + SFML
target_link_libraries(packman
        packman_logic
        sfml-graphics
        sfml-window
        sfml-system
)

# =========================
# INSTALL
# =========================
install(TARGETS packman DESTINATION bin)
