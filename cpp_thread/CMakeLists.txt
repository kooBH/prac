cmake_minimum_required(VERSION 3.5)
project(prac)

set(SRC a.cpp)

set(LINKLIBS pthread)
add_executable(${PROJECT_NAME} ${SRC} )

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 11
    )


target_link_libraries(${PROJECT_NAME} ${LINKLIBS})


