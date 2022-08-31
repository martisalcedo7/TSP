cmake_minimum_required(VERSION 3.10.2)

project(myApp
    VERSION 1.0
    DESCRIPTION "Simulation"
    LANGUAGES CXX)

# add_library(cities STATIC src/cities.cpp)
# target_include_directories(cities PUBLIC ${CMAKE_SOURCE_DIR}/src)

add_executable(myApp src/plot.cpp
                    src/cities.cpp
                    src/solvers.cpp)

target_include_directories(myApp  
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/SFML-2.5.1/include
    # ${CMAKE_SOURCE_DIR}/SFML-2.5.1/lib
)

target_link_libraries(myApp
    PUBLIC
    pthread
    # cities
    ${CMAKE_SOURCE_DIR}/SFML-2.5.1/lib/libsfml-audio.so
    ${CMAKE_SOURCE_DIR}/SFML-2.5.1/lib/libsfml-graphics.so
    ${CMAKE_SOURCE_DIR}/SFML-2.5.1/lib/libsfml-network.so
    ${CMAKE_SOURCE_DIR}/SFML-2.5.1/lib/libsfml-system.so
    ${CMAKE_SOURCE_DIR}/SFML-2.5.1/lib/libsfml-window.so
)

target_compile_options(myApp PRIVATE -Wall -Wextra -Wpedantic -O3)
