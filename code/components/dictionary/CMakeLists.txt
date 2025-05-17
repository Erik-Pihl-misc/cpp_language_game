# Set the minimum required CMake version.
cmake_minimum_required(VERSION 3.20)

# Define the project name and require C++17.
project(Dictionary LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

# Add static library 'Dictionary' with alias 'Language::Dictionary'.
add_library(${PROJECT_NAME} STATIC)
add_library(Language::Dictionary ALIAS ${PROJECT_NAME})

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
    PUBLIC include/dictionary/adapter_interface.h include/dictionary/adapter.h 
           include/dictionary/dictionary.h
    PRIVATE source/adapter_impl.cpp source/adapter_impl.h 
            source/adapter.cpp source/dictionary.cpp)

  # Link libraries.
target_link_libraries(${PROJECT_NAME} PUBLIC Language::Utils)