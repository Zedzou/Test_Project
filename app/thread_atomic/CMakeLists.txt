project(thread_atmoic)

add_executable(thread_atomic thread_atomic.cpp)
target_link_libraries(thread_atomic pthread)