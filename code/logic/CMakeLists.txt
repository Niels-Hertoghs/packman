cmake_minimum_required(VERSION 3.16)
project(packman_logic)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(packman_logic
        world.cpp
        entities/entity.cpp
        entities/movableEntity.cpp
        entities/collectable.cpp
        entities/Ghost.cpp
        entities/manhattanGhost.cpp
        Stopwatch.cpp
        Observer.cpp
        random.cpp
        Score.cpp
        abstractFactory.cpp
)

target_include_directories(packman_logic
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
