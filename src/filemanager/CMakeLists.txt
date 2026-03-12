add_library(filemanager)

target_sources(filemanager
	PRIVATE
		filemanager.cpp

	PUBLIC
	FILE_SET HEADERS
	BASE_DIRS
		${CMAKE_CURRENT_SOURCCE_DIR}
	FILES
		filemanager.h
)

target_link_libraries( filemanager
	gapbuffer
)
