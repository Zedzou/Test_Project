cmake_minimum_required(VERSION 3.13)

set(targetname Label_NYU40)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(${targetname} main.cpp Label_NYU40.h MathUtils.h PlatformIndependence.h)
