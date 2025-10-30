cmake_minimum_required(VERSION 3.16)
project(packman)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Vind SFML (minimaal versie 2.5)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Voeg je broncode toe
add_executable(packman main.cpp)

# Link de SFML-libraries
target_link_libraries(packman sfml-graphics sfml-window sfml-system)