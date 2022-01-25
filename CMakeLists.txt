cmake_minimum_required(VERSION 3.19)
project(out)

set(CMAKE_CXX_STANDARD_REQUIRED true)

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

add_executable(
    out
    main.cpp
    Triangle.cpp
    Ring.cpp
    Graph.cpp
    Fluid.cpp
    Vector2D.cpp
    GameOfLife.cpp
    CodeTyping.cpp
)
target_link_libraries(
    out
    sfml-graphics
    sfml-window
    sfml-audio
)
