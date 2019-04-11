# Require a recent version of cmake
cmake_minimum_required(VERSION 3.3.2 FATAL_ERROR)

# This project is C++ based.
project(test_prj CXX)

# Instruct cmake to find the HPX settings
find_package(HPX REQUIRED)

add_executable(aa
  #  main_with_hpx_main.cpp
  main.cpp
  )
hpx_setup_target(aa)

target_link_libraries(aa
  hpx_iostreams
  )
