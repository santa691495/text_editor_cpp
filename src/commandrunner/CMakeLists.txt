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
