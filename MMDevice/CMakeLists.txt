# CMAKE version of Ubuntu 16.04 is 3.5.
cmake_minimum_required(VERSION 3.5)
project(test)

set(SRC)
set(INCL)
set(LINKLIBS)
set(COMPILE_OPTION)

include(lib/RtAudioWrapper/RtAudio.cmake)

list(APPEND SRC
	cleanup.h
	common.h
	log.h
	loopback-capture.h
	loopback-capture.cpp
	prefs.h
	prefs.cpp
	functiondiscoverykeys_devpkey.h
	
	test.cpp
  )
list(APPEND INCL
  ${CMAKE_CURRENT_LIST_DIR}/.
  )
list(APPEND LINKLIBS
	avrt.lib
	ole32.lib
	winmm.lib
	odbc32.lib
	odbccp32.lib
	dsound.lib
  )
if(MSVC)
  list(APPEND COMPILE_OPTION
	/D"UNICODE"
	/D"_UNICODE"
	 )
else()
  list(APPEND COMPILE_OPTION
    )
endif()

add_executable(${PROJECT_NAME} ${SRC})
target_include_directories(${PROJECT_NAME}    PRIVATE    ${INCL}  )
target_link_libraries(${PROJECT_NAME} ${LINKLIBS})
target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTION} )
set_target_properties(${PROJECT_NAME} PROPERTIES  CXX_STANDARD 17 )