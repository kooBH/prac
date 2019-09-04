cmake_minimum_required(VERSION 3.5)
project(eigen)

set(LINKLIBS)
set(COMPILE_OPTION)
set(SRC)
set(INCL)


list(APPEND SRC
  test_eigen.hpp
  test_plasma.hpp
  eigen_solver.hpp
  test_lapack.hpp
  main.cpp
  )

  list(APPEND INCL
  # path to egien lib
	${CMAKE_CURRENT_SOURCE_DIR}/eigen
	${CMAKE_CURRENT_SOURCE_DIR}/openblas
  )

add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME}
	PRIVATE
	${INCL}
  )


list(APPEND LINKLIBS
   ${PROJECT_SOURCE_DIR}/openblas/libopenblas.so
)

target_link_libraries(${PROJECT_NAME} ${LINKLIBS})
target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTION} )
set_target_properties(${PROJECT_NAME} PROPERTIES  CXX_STANDARD 14 )


