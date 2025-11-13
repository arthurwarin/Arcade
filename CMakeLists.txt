cmake_minimum_required(VERSION 3.20)
project(arcade)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fno-gnu-unique -fPIC")
# Set the output directory for all libraries
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
# Set the output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

if(release)
    message(STATUS "Building in release mode")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
    set(CMAKE_BUILD_TYPE Release)
else()
    message(STATUS "Building in debug mode")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3")
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Abstract sources (needed by both core and libraries)
file(GLOB_RECURSE ABSTRACT_SOURCES
    "Abstract/*.cpp"
)

# Core sources for the main executable
file(GLOB_RECURSE CORE_SOURCES
    "Core/*.cpp"
)

# Exclude loop files from compilation
set(EXCLUDED_FILES
    "${CMAKE_SOURCE_DIR}/game_loop.cpp"
    "${CMAKE_SOURCE_DIR}/Nibbler_loop.cpp"
)

# Menu sources (needed by core only)
file(GLOB_RECURSE MENU_SOURCES
    "Games/Menu/*.cpp"
)

# Add the main.cpp file (which is at the root)
list(APPEND CORE_SOURCES "${CMAKE_SOURCE_DIR}/main.cpp")

# Remove excluded files
list(REMOVE_ITEM CORE_SOURCES ${EXCLUDED_FILES})

# Main executable
add_executable(arcade ${CORE_SOURCES} ${ABSTRACT_SOURCES} ${MENU_SOURCES})

# Create shared libraries for each graphical library
file(GLOB_RECURSE SFML_SOURCES "Graphical_libraries/SFML/*.cpp")
file(GLOB_RECURSE SDL2_SOURCES "Graphical_libraries/SDL2/*.cpp")
file(GLOB_RECURSE NCURSES_SOURCES "Graphical_libraries/Ncurses/*.cpp")

# Create shared libraries for each game
file(GLOB_RECURSE SNAKE_SOURCES "Games/Snake/*.cpp")
file(GLOB_RECURSE NIBBLER_SOURCES "Games/Nibbler/*.cpp")

# Make sure we don't accidentally include the standalone loop files
list(REMOVE_ITEM SNAKE_SOURCES ${EXCLUDED_FILES})
list(REMOVE_ITEM NIBBLER_SOURCES ${EXCLUDED_FILES})

# Find required packages for each library
find_package(SFML COMPONENTS graphics window system REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

# SFML library
add_library(arcade_sfml SHARED ${SFML_SOURCES} ${ABSTRACT_SOURCES})
target_link_libraries(arcade_sfml sfml-graphics sfml-window sfml-system)
set_target_properties(arcade_sfml PROPERTIES PREFIX "")
set_target_properties(arcade_sfml PROPERTIES COMPILE_FLAGS "-fPIC")

# SDL2 library
add_library(arcade_sdl2 SHARED ${SDL2_SOURCES} ${ABSTRACT_SOURCES})
target_link_libraries(arcade_sdl2 SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf)
set_target_properties(arcade_sdl2 PROPERTIES PREFIX "")
set_target_properties(arcade_sdl2 PROPERTIES COMPILE_FLAGS "-fPIC")

# Ncurses library
add_library(arcade_ncurses SHARED ${NCURSES_SOURCES} ${ABSTRACT_SOURCES})
target_link_libraries(arcade_ncurses ${CURSES_LIBRARIES})
set_target_properties(arcade_ncurses PROPERTIES PREFIX "")
set_target_properties(arcade_ncurses PROPERTIES COMPILE_FLAGS "-fPIC")

# Snake game library
add_library(arcade_snake SHARED ${SNAKE_SOURCES} ${ABSTRACT_SOURCES})
set_target_properties(arcade_snake PROPERTIES PREFIX "")
set_target_properties(arcade_snake PROPERTIES COMPILE_FLAGS "-fPIC")

# Nibbler game library
add_library(arcade_nibbler SHARED ${NIBBLER_SOURCES} ${ABSTRACT_SOURCES})
set_target_properties(arcade_nibbler PROPERTIES PREFIX "")
set_target_properties(arcade_nibbler PROPERTIES COMPILE_FLAGS "-fPIC")

# Menu library
add_library(arcade_menu SHARED ${ABSTRACT_SOURCES} ${MENU_SOURCES} "${CMAKE_SOURCE_DIR}/Core/DLloader.cpp")
set_target_properties(arcade_menu PROPERTIES PREFIX "")
set_target_properties(arcade_menu PROPERTIES COMPILE_FLAGS "-fPIC")

# Link main executable with required libraries
target_link_libraries(arcade ${CURSES_LIBRARIES} dl)

# Include directories for the main executable
target_include_directories(arcade 
    PUBLIC 
        "${CMAKE_SOURCE_DIR}/Abstract"
        "${CMAKE_SOURCE_DIR}/Core"
        "${CMAKE_SOURCE_DIR}/interface"
        "${CMAKE_SOURCE_DIR}/Games/Menu"
)

# Add include directories for each library
target_include_directories(arcade_sfml PUBLIC "${CMAKE_SOURCE_DIR}/Abstract" "${CMAKE_SOURCE_DIR}/interface")
target_include_directories(arcade_sdl2 PUBLIC "${CMAKE_SOURCE_DIR}/Abstract" "${CMAKE_SOURCE_DIR}/interface")
target_include_directories(arcade_ncurses PUBLIC "${CMAKE_SOURCE_DIR}/Abstract" "${CMAKE_SOURCE_DIR}/interface")
target_include_directories(arcade_snake PUBLIC "${CMAKE_SOURCE_DIR}/Abstract" "${CMAKE_SOURCE_DIR}/interface")
target_include_directories(arcade_nibbler PUBLIC "${CMAKE_SOURCE_DIR}/Abstract" "${CMAKE_SOURCE_DIR}/interface")
target_include_directories(arcade_menu PUBLIC "${CMAKE_SOURCE_DIR}/Abstract" "${CMAKE_SOURCE_DIR}/interface" "${CMAKE_SOURCE_DIR}/Core")

add_custom_target(clean_build
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/*
    COMMENT "Clean build cache"
)