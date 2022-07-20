cmake_minimum_required(VERSION 3.5)

project(osgqt LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

# OSG 
set(OSG_BINARY_DIR /home/zed/Project/libs/OpenSceneGraph/bin)
include_directories(${OSG_BINARY_DIR}/include)
set(OSG_LIBRARIES ${OSG_BINARY_DIR}/lib/libosg.so
                  ${OSG_BINARY_DIR}/lib/libosgViewer.so
                  ${OSG_BINARY_DIR}/lib/libosgDB.so
                  ${OSG_BINARY_DIR}/lib/libosgGA.so
                  ${OSG_BINARY_DIR}/lib/libOpenThreads.so)

add_executable(osgqt
  main.cpp
  osgqt.cpp
  osgqt.h
  osgqt.ui
  control.ui
  QtOsgView.cpp
  QtOsgView.h
)

target_link_libraries(osgqt PRIVATE Qt5::Widgets
                            PUBLIC ${OSG_LIBRARIES})
