cmake_minimum_required(VERSION 3.13)
set(targetname libzip_testProject)

# setting
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
set(CMAKE_PREFIX_PATH ${PROJECT_BINARY_DIR} ${CMAKE_PREFIX_PATH})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# set compiler flags
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libstdc++ -Wno-deprecated-declarations -Wno-unused-function")
endif()
if(NOT MSVC_IDE)
	set(CFLAGS_WARN "-Wall -Wextra -Wno-unused-parameter -Wno-strict-aliasing")
	set(CMAKE_CXX_FLAGS "-fPIC ${CFLAGS_WARN} ${CMAKE_CXX_FLAGS}")
endif()

# envirment
set(WITH_LIBZIP ON)
include(Uselibzip)

# target and target link
add_executable(${targetname} main.cpp)
include(Linklibzip)
