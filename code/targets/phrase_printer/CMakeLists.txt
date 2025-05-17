# Set application target.
set(TARGET PhrasePrinter)

# Add executable for the application target.
add_executable(${TARGET} source/main.cpp)

# Enable all warnings, make warnings generate compilation errors.
target_compile_options(${TARGET} PRIVATE -Wall -Werror)

# Link library 'Language::Dictionary' to use the language dictionary implementation.
target_link_libraries(${TARGET} PRIVATE Language::Dictionary)

#  Override output directory set in root, store executable in the 'utils' directory.
set_target_properties(${TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/utils)
