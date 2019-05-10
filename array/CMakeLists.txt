cmake_minimum_required(VERSION 3.5)
project(arrays)


add_executable(${PROJECT_NAME} main.cpp array.h)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 11
    )
