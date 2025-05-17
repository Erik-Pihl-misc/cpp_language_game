SET(TARGET LanguageGame)
add_executable(${TARGET} source/main.cpp)
target_compile_options(${TARGET} PRIVATE -Wall -Werror)
target_link_libraries(${TARGET} PRIVATE Language::Dictionary Language::Game)