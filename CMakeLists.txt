cmake_minimum_required(VERSION 3.10.2)

project(myApp
    VERSION 1.0
    DESCRIPTION "Simulation"
    LANGUAGES CXX)


add_executable(myApp src/main.cpp)

target_include_directories(myApp  
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/SFML-2.5.1/include
    # ${CMAKE_SOURCE_DIR}/SFML-2.5.1/lib
)

# target_link_libraries(myApp
# PRIVATE python3.6m)

target_link_libraries(myApp
    PUBLIC
    pthread
    ${CMAKE_SOURCE_DIR}/SFML-2.5.1/lib/libsfml-audio.so
    ${CMAKE_SOURCE_DIR}/SFML-2.5.1/lib/libsfml-graphics.so
    ${CMAKE_SOURCE_DIR}/SFML-2.5.1/lib/libsfml-network.so
    ${CMAKE_SOURCE_DIR}/SFML-2.5.1/lib/libsfml-system.so
    ${CMAKE_SOURCE_DIR}/SFML-2.5.1/lib/libsfml-window.so
)

# target_compile_features(myApp PRIVATE cxx_std_17)

target_compile_options(myApp PRIVATE -Wall -Wextra -Wpedantic)
