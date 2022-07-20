set(targetname NormalPointCloud)

include(Usetinyply)
add_executable(${targetname} NormalPointCloud.cpp)
# include(LinkPCL)
include(Linktinyply)