## Original Shape of CMake for CUDA

cmake_minimum_required(VERSION 3.15)

### Specify Compiler ###
set(CMAKE_CXX_COMPILER /usr/bin/g++-5)
set(CUDA_TOOLKIT_ROOT_DIR /usr/local/cuda-9.2)
set(CMAKE_CUDA_COMPILER ${CUDA_TOOLKIT_ROOT_DIR}/bin/nvcc)
set(CUDA_LIBRARIES_DIR ${CUDA_TOOLKIT_ROOT_DIR}/lib64)

set(SRC)
set(LIBS)
set(OPS)
set(INCL)

message(STATUS "Found CUDA ${CUDA_VERSION_STRING} at ${CUDA_TOOLKIT_ROOT_DIR}")

project(cublas LANGUAGES CXX CUDA)
##############################################################################


list(APPEND SRC
  dgemm.cu
  )

list(APPEND INCL
  )

list(APPEND OPS
  )

message(STATUS 
  "*** CUDA_LIBRARIES ***"
  ${CUDA_LIBRARIES_DIR}/libcublas.so
  
  )

list(APPEND LIBS
  ${CUDA_LIBRARIES_DIR}/libcublas.so
  ${CUDA_LIBRARIES_DIR}/libcudart.so
  )



##############################################################################

add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${INCL}
  )
target_link_libraries(${PROJECT_NAME} ${LIBS})
#target_compile_options(${PROJECT_NAME} ${OPS})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 11 CUDA_STANDARD 11)


