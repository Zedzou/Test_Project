# external package libzip
set(NAME libzip)
set(URL "git@github.com:nih-at/libzip.git")
set(${NAME}_INSTALL_DIR  ${CMAKE_BINARY_DIR}/external/${NAME})

if (NOT EXISTS ${${NAME}_INSTALL_DIR}/CMakeLists.txt)

        find_package(Git)
        if(NOT EXISTS ${${NAME}_INSTALL_DIR})
        file(MAKE_DIRECTORY ${${NAME}_INSTALL_DIR})
        endif()

        execute_process( COMMAND ${GIT_EXECUTABLE} clone ${URL} ${NAME} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/external )

        if(NOT EXISTS ${${NAME}_INSTALL_DIR}/build)
        file(MAKE_DIRECTORY ${${NAME}_INSTALL_DIR}/build)
        endif()

        execute_process( COMMAND cmake -DCMAKE_INSTALL_PREFIX=${${NAME}_INSTALL_DIR}/bin .. WORKING_DIRECTORY ${${NAME}_INSTALL_DIR}/build )
        execute_process( COMMAND make install WORKING_DIRECTORY ${${NAME}_INSTALL_DIR}/build )

        set(${NAME}_FOUND 1 CACHE STRING " ")

endif()

if ( ${${NAME}_FOUND} )
        find_package(libzip REQUIRED PATHS ${${NAME}_INSTALL_DIR}/bin/lib/cmake NO_DEFAULT_PATH)
endif()