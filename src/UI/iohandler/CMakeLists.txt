add_library(iohandler)

target_sources(iohandler
	PRIVATE
		iohandler.cpp

	PUBLIC
	FILE_SET HEADERS
	BASE_DIRS
		${CMAKE_CURRENT_SOURCE_DIR}
	FILES
		iohandler.h
)

target_link_libraries( iohandler PRIVATE ${CURSES_LIBRARIES} )


