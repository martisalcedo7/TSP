cmake_minimum_required(VERSION 3.10.2)

project(TSP
    VERSION 1.0
    DESCRIPTION "Simulation"
    LANGUAGES CXX)

# add_library(cities STATIC src/cities.cpp)
# target_include_directories(cities PUBLIC ${CMAKE_SOURCE_DIR}/src)

add_executable(TSP src/main.cpp
                    src/cities.cpp
                    src/solvers.cpp
                    src/utils.cpp)

target_include_directories(TSP  
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/SFML-2.5.1/include
    ${CMAKE_SOURCE_DIR}/fonts
    # ${CMAKE_SOURCE_DIR}/SFML-2.5.1/lib
)

target_link_libraries(TSP
    PUBLIC
    # cities
    ${CMAKE_SOURCE_DIR}/SFML-2.5.1/lib/libsfml-audio.so
    ${CMAKE_SOURCE_DIR}/SFML-2.5.1/lib/libsfml-graphics.so
    ${CMAKE_SOURCE_DIR}/SFML-2.5.1/lib/libsfml-network.so
    ${CMAKE_SOURCE_DIR}/SFML-2.5.1/lib/libsfml-system.so
    ${CMAKE_SOURCE_DIR}/SFML-2.5.1/lib/libsfml-window.so
)

# set_property(TARGET myApp PROPERTY CXX_STANDARD 17)
# set(CMAKE_CXX_COMPILER_VERSION "8.4.0")


target_compile_options(TSP PRIVATE -Wall -Wextra -Wpedantic -O3)
