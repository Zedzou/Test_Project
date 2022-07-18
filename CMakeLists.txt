cmake_minimum_required(VERSION 3.13)

# setting
set(targetname OSG_Render)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-funcation")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libstdc++ -Who-deprecated-declarations -Who-unused-funcation")
endif()

# exeternal package binary path
set(OSG_BINARY_PATH /home/zed/Project/Libs/OpenSceneGraph/bin)
set(Eigen3_BINARY_PATH /home/zed/Project/Libs/eigen/bin)

add_subdirectory(elements)