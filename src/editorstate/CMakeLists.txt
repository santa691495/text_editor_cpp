add_library(editorstate)

target_sources( editorstate
    PRIVATE
        editorstate.cpp

    PUBLIC
    FILE_SET HEADERS
    BASE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}
    FILES 
        editorstate.h
)

target_link_libraries(editorstate 
    ${CURSES_LIBRARIES}
)