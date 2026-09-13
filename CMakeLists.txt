cmake_minimum_required(VERSION 3.25)
project(EcijaEngine LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PROJECT_SOURCE_FILES
  source/main.cpp
  source/Game.hpp
  source/Game.cpp
)

add_subdirectory(engine)
include_directories(
  engine/source
)
add_executable(EcijaEngine  ${PROJECT_SOURCE_FILES})

target_link_libraries(EcijaEngine PRIVATE Engine)
