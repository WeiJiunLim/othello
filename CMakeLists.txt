cmake_minimum_required(VERSION 3.16)

project(othello)

# =====================================================================================================================
# C++ Standard
# =====================================================================================================================

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# =====================================================================================================================
# Project Warnings Library
# =====================================================================================================================

add_library(project_warnings INTERFACE)

target_compile_options(project_warnings INTERFACE
    -Wall
    -Wextra
    -Wpedantic
)

# =====================================================================================================================
# Display Library
# =====================================================================================================================

add_library(display
    src/display.cpp
)
target_include_directories(display PUBLIC include)
target_link_libraries(display PRIVATE project_warnings)

# =====================================================================================================================
# Game Library
# =====================================================================================================================

add_library(game
    src/game.cpp
)
target_include_directories(game PUBLIC include)
target_link_libraries(game PRIVATE project_warnings)

# =====================================================================================================================
# Input Library
# =====================================================================================================================

add_library(input
    src/input.cpp
)
target_include_directories(input PUBLIC include)
target_link_libraries(input PRIVATE project_warnings)

# =====================================================================================================================
# Main Executable
# =====================================================================================================================

add_executable(othello
    src/main.cpp
)

target_link_libraries(othello
    PRIVATE
        project_warnings
        display
        game
        input)
