cmake_minimum_required(VERSION 3.20)
project(language_game)
include_directories(../inc)

add_executable(run_game ../src/main.cpp ../src/utils.cpp ../src/dictionary.cpp)
target_compile_options(run_game PRIVATE -Wall -Werror)
set_target_properties(run_game PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../)

add_executable(remove_duplicates ../src/remove_duplicates.cpp ../src/utils.cpp ../src/dictionary.cpp)
target_compile_options(remove_duplicates PRIVATE -Wall -Werror)
set_target_properties(remove_duplicates PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../utilities)

add_executable(print_phrases ../src/print_phrases.cpp ../src/utils.cpp ../src/dictionary.cpp)
target_compile_options(print_phrases PRIVATE -Wall -Werror)
set_target_properties(print_phrases PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../utilities) 
