cmake_minimum_required(VERSION 3.20)

project(OpenGLProject)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(app
    src/move.cpp
    src/glad.c
)

target_include_directories(app PRIVATE include)

target_link_libraries(app
    OpenGL::GL
    glfw
)
