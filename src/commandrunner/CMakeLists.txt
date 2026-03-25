add_library(cmdrunner)

target_sources( cmdrunner
	PRIVATE
		cmdrunner.cpp

	PUBLIC
	FILE_SET HEADERS
	BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
	FILES
		cmdrunner.h
)	

target_link_libraries( cmdrunner
	cmd_obj
	gapbuffer
	filemanager
)

add_library(cmdstatus INTERFACE)
target_include_directories(cmdstatus INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} )
target_sources(cmdstatus INTERFACE cmdstatus.h)

add_library(cmdtype INTERFACE cmdtype.h)
target_include_directories(cmdtype INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} )
target_sources(cmdtype INTERFACE cmdtype.h)
