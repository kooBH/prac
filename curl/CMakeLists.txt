cmake_minimum_required(VERSION 3.5)
project(curl)

#########################################
#                                       #
#               CURL                    #
#       https://curl.haxx.se/           #
#                                       #
#########################################

# Library Header
list(APPEND SRC
    lib/curl/curl.h
    lib/curl/curlver.h
    )
# Curl Warpper
list(APPEND SRC 
  CppUrl.h 
  )

if(UNIX)
list(APPEND LINKLIBS
    ${PROJECT_SOURCE_DIR}/lib/curl/libcurl.so
    
    )
else()
list(APPEND LINKLIBS
    ${PROJECT_SOURCE_DIR}/lib/curl/libcurl.lib)
endif()

include_directories(
    lib
)

add_executable(${PROJECT_NAME} test.cpp ${SRC})



target_link_libraries(${PROJECT_NAME} ${LINKLIBS})
set_target_properties(${PROJECT_NAME} PROPERTIES  CXX_STANDARD 14 )
