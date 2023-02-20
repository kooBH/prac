cmake_minimum_required(VERSION 3.5)
project(sample)

set(LINKLIBS)
set(COMPILE_OPTION)
set(DLL_SRC)
set(EXE_SRC)
set(INCL)
 

list(APPEND DLL_SRC	
	A.cpp
	A.h
	B.cpp
	B.h
	wrapper.h
	wrapper.cpp
)

list(APPEND EXE_SRC	
	test.cpp
	wrapper.h
)

list(APPEND include
	${CMAKE_CURRENT_LIST_DIR}
	)

list(APPEND LINKLIBS
	lib_sample
)


add_library(lib_${PROJECT_NAME} SHARED ${DLL_SRC})
target_include_directories(lib_${PROJECT_NAME}	PRIVATE	${INCL}  )
target_compile_options(lib_${PROJECT_NAME} PRIVATE ${COMPILE_OPTION} /D_EXPORT_ )
set_target_properties(lib_${PROJECT_NAME} PROPERTIES  CXX_STANDARD 14 )

add_executable(${PROJECT_NAME} ${EXE_SRC})
target_include_directories(${PROJECT_NAME}	PRIVATE	${INCL}  )
target_link_libraries(${PROJECT_NAME} ${LINKLIBS})
target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTION} )

