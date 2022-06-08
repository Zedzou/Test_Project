# Uselibzip.cmake
find_package(libzip QUIET)

if(WITH_LIBZIP)
    MESSAGE("WITH_LIBZIP: " ${WITH_LIBZIP})
    include(External_libzip)
endif()