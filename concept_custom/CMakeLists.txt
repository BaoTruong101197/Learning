project(custom)

set(CMAKE_CXX_STANDARD 17)

add_executable(custom main.cpp)
target_link_libraries(custom -pthread)