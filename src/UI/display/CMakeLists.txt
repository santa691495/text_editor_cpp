add_library(display)

target_sources(display
	PRIVATE
		display.cpp
	
	PUBLIC
		FILE_SET HEADERS
		BASE_DIRS
			${CMAKE_CURRENT_SOURCE_DIR}
		FILES
			display.h

)	

target_link_libraries( display
	${CURSES_LIBRARIES}
)
