cmake_minimum_required(VERSION 3.5)
project(json_prac)

set(SRC json.hpp main.cpp)

add_executable(${PROJECT_NAME} ${SRC})


set_target_properties(${PROJECT_NAME} PROPERTIES  CXX_STANDARD 14 )
