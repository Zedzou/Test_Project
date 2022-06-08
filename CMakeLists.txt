cmake_minimum_required(VERSION 3.13)
set(targetname PathTool)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(${targetname} main.cpp PathTool.cpp PathTool.hpp)