
cmake_minimum_required(VERSION 3.5)

project(python_test)

set(LINKLIBS)
set(COMPILE_OPTION)
set(SRC)

list(APPEND SRC
   main.cpp)

find_package( PythonLibs 3 REQUIRED )
include_directories(${PYTHON_INCLUDE_DIRS})
list(APPEND LINKLIBS ${PYTHON_LIBRARIES}
  )

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} ${LINKLIBS}  )
target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTION}   )

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 11
    )


