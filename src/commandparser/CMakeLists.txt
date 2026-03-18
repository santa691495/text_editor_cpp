add_library(cmdparser)

target_sources(cmdparser
	PRIVATE
		cmdparser.cpp
	PUBLIC
	FILE_SET HEADERS
	BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
	FILES
		cmdparser.h
)

target_link_libraries(cmdparser
	cmd_obj
)
	
