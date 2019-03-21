
cmake_minimum_required(VERSION 3.5)

project(so_test)


add_executable(${PROJECT_NAME} c.c hi.h)  
add_library(hi SHARED hi.c)  
target_link_libraries(${PROJECT_NAME} hi)  
