cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(
  slow
  VERSION 0.1.0
  LANGUAGES C
  )

# we're doing c99
set(CMAKE_C_STANDARD 99)

# export compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# include files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# source files
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
