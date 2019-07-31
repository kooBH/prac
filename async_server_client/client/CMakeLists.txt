cmake_minimum_required(VERSION 3.5)
project(a)


set(SRC)
set(HEAD)
set(LINKLIBS)
set(INCL)

list(APPEND SRC
  main.cpp
  )

#########################################
#               CURL                    #
#       https://curl.haxx.se/           #
#########################################

# Library Header
list(APPEND SRC
    curl/curl.h
    curl/curlver.h
    )

list(APPEND LINKLIBS
    ${PROJECT_SOURCE_DIR}/curl/libcurl.so
    pthread
    )


add_executable(${PROJECT_NAME} ${SRC} ${HEAD})

list(APPEND INCL
	${CMAKE_CURRENT_SOURCE_DIR}/curl
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(${PROJECT_NAME}
	PRIVATE
	${INCL}
  )

target_link_libraries(${PROJECT_NAME} ${LINKLIBS})
target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTION} )
set_target_properties(${PROJECT_NAME} PROPERTIES  CXX_STANDARD 14 )
