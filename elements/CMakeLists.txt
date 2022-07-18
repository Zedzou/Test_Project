set(targetname osg_render)

find_package(OSG)

set(sources main.cc 
            dataLoader/dataLoader.cpp)

set(includes Camera.h
             CoordinateAxis.h
             dataLoader/dataLoader.h
             Light.h
             Models.h)

include(UseEigen3)
add_executable(${targetname} ${sources} ${includes})
include(LinkOSG)
include(LinkEigen3)