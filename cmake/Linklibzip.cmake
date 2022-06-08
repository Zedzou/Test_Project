
set(libzip_lib ${PROJECT_BINARY_DIR}/external/libzip/bin/lib/libzip.so)
target_link_libraries(${targetname} ${libzip_lib})