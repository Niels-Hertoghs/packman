cmake_minimum_required(VERSION 3.16)
project(packman)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Vind SFML
find_package(SFML 2.6 COMPONENTS system window graphics)

# Voeg logic subdirectory toe
add_subdirectory(code/logic)

# --- Executable ---
add_executable(packman
        main.cpp
        code/view/game.cpp
        code/view/camera.cpp
        code/view/worldView.cpp
        code/view/ScoreView.cpp
        code/view/observerView.h

        code/view/entities/entityView.cpp
        code/view/entities/movableEntityView.cpp
        code/view/entities/collectableView.cpp
        code/view/entities/ghostView.cpp

        code/view/state_maneger/stateManeger.cpp
        code/view/state_maneger/state.cpp
        code/view/state_maneger/make_text.cpp

        code/view/concreteFactory.cpp
)

target_include_directories(packman
        PRIVATE code/view
)

target_link_libraries(packman
        PRIVATE
        packman_logic
        sfml-graphics
        sfml-window
        sfml-system
)

install(TARGETS packman DESTINATION bin)
