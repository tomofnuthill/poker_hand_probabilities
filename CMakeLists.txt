cmake_minimum_required(VERSION 3.25)
project(poker)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_BUILD_TYPE Debug)

file(GLOB_RECURSE SOURCES "./src/*.cpp" "./src/*/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES} main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE .)

