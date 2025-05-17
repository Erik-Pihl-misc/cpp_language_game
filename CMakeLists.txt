# Set the minimum required CMake version.
cmake_minimum_required(VERSION 3.20)

# Define the project name.
project(Language)

# Set the C++ standard for all targets.
set(CMAKE_CXX_STANDARD 17)

# Set the default output directory for executables.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# Add the main source directory containing components and targets.
add_subdirectory(code)