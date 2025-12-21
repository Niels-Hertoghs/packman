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

# Logic gebruikt enkel sfml-system
target_link_libraries(packman_logic
        PUBLIC sfml-system
)
