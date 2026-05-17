add_library(filemanager)

target_sources(filemanager
	PRIVATE
		filemanager.cpp

	PUBLIC
	FILE_SET HEADERS
	BASE_DIRS
		${CMAKE_CURRENT_SOURCE_DIR}
	FILES
		filemanager.h
)

target_link_libraries( filemanager
	gapbuffer
)

add_library(filestatus INTERFACE)
target_include_directories(filestatus INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(filestatus INTERFACE filestatus.h)