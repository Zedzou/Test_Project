set(targetname InsatnceID)

set(tiny_INCLUDE_PATH /home/zed/Project/libs/tinyply/bin/include)
set(tiny_LIBRARY_PATH /home/zed/Project/libs/tinyply/bin/lib/libtinyply.a)

include_directories(${tiny_INCLUDE_PATH})
add_executable(${targetname} InstanceID.cpp)
target_link_libraries(${targetname} ${tiny_LIBRARY_PATH} ${PCL_LIBRARIES})
# include(LinkPCL)
# include(Linktinyply)