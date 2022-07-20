project(Thread_mutex)

add_executable(Thread_mutex thread_mutex.cpp)
target_link_libraries(Thread_mutex pthread)
