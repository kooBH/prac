project(c)
cmake_minimum_required(VERSION 3.0)


include_directories(../cpp)
add_executable(c main.c)
target_link_libraries(c /home/kbh/work/prac/call_cpp_in_c/cpp/build/libA.so)