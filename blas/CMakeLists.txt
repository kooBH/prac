cmake_minimum_required(VERSION 3.5)
project(blas_test)


add_executable(${PROJECT_NAME} test.cpp)
target_compile_options(${PROJECT_NAME} PRIVATE -fopenmp -std=c++11)
target_link_libraries(${PROJECT_NAME} libopenblas.so -fopenmp m)
