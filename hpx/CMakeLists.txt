# Require a recent version of cmake
cmake_minimum_required(VERSION 3.3.2 FATAL_ERROR)

# This project is C++ based.
project(your_app CXX)

# Instruct cmake to find the HPX settings
find_package(HPX REQUIRED)

add_executable(hello_world 
  hello_world.cpp)
hpx_setup_target(hello_world)

target_link_libraries(hello_world
  hpx_iostreams
  )
