target_link_libraries(${targetname} PUBLIC ${OSG_BINARY_PATH}/lib/libosg.so
                                    PUBLIC ${OSG_BINARY_PATH}/lib/libosgViewer.so
                                    PUBLIC ${OSG_BINARY_PATH}/lib/libosgDB.so
)

target_include_directories(${targetname} PUBLIC ${OpenSceneGraph_INCLUDE_DIRS})
