cmake_minimum_required(VERSION 3.10)

# Set project name
project(Menace_Graphics)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

#include the directories, prevents the relative paths problem with the build shell script
include_directories(include)

# Add an executable
add_executable(${PROJECT_NAME} src/main.cpp src/glad.c)

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} glfw dl ${OPENGL_gl_LIBRARIES})