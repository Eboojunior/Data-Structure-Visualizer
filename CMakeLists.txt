cmake_minimum_required(VERSION 3.10)
project(DataStructureVisualizer)

set(CMAKE_CXX_STANDARD 17)

# ImGui setup
add_subdirectory(imgui)

# SDL3 setup
find_package(SDL3 REQUIRED)
include_directories(${SDL3_INCLUDE_DIRS})

# OpenGL
find_package(OpenGL REQUIRED)

add_executable(DataStructureVisualizer main.cpp)

target_link_libraries(DataStructureVisualizer
    imgui
    SDL3::SDL3
    OpenGL::GL
)
