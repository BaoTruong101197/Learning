project(custom)

set(CMAKE_CXX_STANDARD 11)

add_executable(custom main.cpp)
target_link_libraries(custom -pthread)