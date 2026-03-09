# TODO: fix target sources
add_library(gapbuffer)

target_sources( gapbuffer
	PRIVATE
		gapbuffer.cpp

	PUBLIC
	FILE SET HEADERS
	BASE_DIR
		${CMAKE_CURRENT_SOURCE_DIR}
	FILES
		gapbuffer.h
)
