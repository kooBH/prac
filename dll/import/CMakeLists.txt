cmake_minimum_required(VERSION 3.5)
project(import)

set(LINKLIBS)
set(COMPILE_OPTION)
set(SRC)
set(INCL)
 

list(APPEND SRC	
	import.cpp
)

list(APPEND INCL 
	../export
)

list(APPEND LINKLIBS 
	export
)

add_executable(${PROJECT_NAME} ${SRC})
target_include_directories(${PROJECT_NAME}	PRIVATE	${INCL}  )
target_link_libraries(${PROJECT_NAME} ${LINKLIBS})
target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTION} )
set_target_properties(${PROJECT_NAME} PROPERTIES  CXX_STANDARD 14 )



