# CMAKE version of Ubuntu 16.04 LTS is 3.5.
cmake_minimum_required(VERSION 3.5)
project(TEST)

option(ARM "Using gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu for ARM board" OFF)

message("[Hint] Set options : -D<OPTION>=<ON|OFF>  | e.g.: cmake .. -DARM=OFF")
message("[ BUILD OPTION ]")
message(STATUS ARM : ${ARM})

if(ARM)
	set(CMAKE_SYSTEM_NAME Linux)
	set(CMAKE_SYSTEM_PROCESSOR arm)
	set(CMAKE_C_STANDARD11)

	set(tools ${CMAKE_CURRENT_LIST_DIR}/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu)
	set(CMAKE_C_COMPILER ${tools}/bin/aarch64-linux-gnu-gcc)
	set(CMAKE_CXX_COMPILER ${tools}/bin/aarch64-linux-gnu-g++)

	set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
	set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
	set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
	set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
endif()

add_executable(TEST test.cpp)