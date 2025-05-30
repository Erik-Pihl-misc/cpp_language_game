# Set the minimum required CMake version.
cmake_minimum_required(VERSION 3.20) 

# Define the project name and require C++17.
project(DictionaryTest) 

set(CMAKE_CXX_STANDARD 17)

# Locate package GTest.
find_package(GTest REQUIRED) 

# Include GTest directories.
include_directories(${PROJECT_NAME} ${GTEST_INCLUDE_DIRS}) 

# Add test executable.
add_executable(${PROJECT_NAME} adapter_test.cpp dictionary_test.cpp) 

# Enable all warnings, make warnings generate compilation errors.
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror) 

# Link libraries.
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} pthread Language::Dictionary)

#  Override output directory set in root, store executable in the 'test' directory.
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/test)
