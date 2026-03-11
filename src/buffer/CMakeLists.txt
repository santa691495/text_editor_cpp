# TODO: fix target sources
add_library(gapbuffer)

target_sources(gapbuffer
	PRIVATE
		gapbuffer.cpp

	PUBLIC
	FILE_SET HEADERS
	BASE_DIRS
		${CMAKE_CURRENT_SOURCE_DIR}
	FILES
		${CMAKE_CURRENT_SOURCE_DIR}/gapbuffer.h
)
