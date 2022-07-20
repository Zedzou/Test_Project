set(targetname std_map)

include(UseEigen3)
add_executable(${targetname} main.cpp)
include(LinkEigen3)