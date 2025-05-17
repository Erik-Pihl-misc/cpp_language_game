# Set the minimum required CMake version.
cmake_minimum_required(VERSION 3.20)

# Define the project name and require C++17.
project(Utils LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

# Add static library 'Utils' with alias 'Language::Utils'.
add_library(${PROJECT_NAME} STATIC)
add_library(Language::Utils ALIAS ${PROJECT_NAME})

# Specify include directories:
# - 'include' is public (visible to consumers of the library)
# - 'source' is private (internal use only)
target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/source)

# Specify target source files:
# - Headers in 'include' are public
# - Sources and headers in 'source' are private
target_sources(${PROJECT_NAME}
    PUBLIC include/utils/phrase.h include/utils/utils.h
    PRIVATE source/utils.cpp)