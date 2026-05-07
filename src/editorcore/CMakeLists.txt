add_library(editorcore)

target_sources(editorcore 
    PRIVATE 
        editorcore.cpp   

    PUBLIC 
    FILE_SET HEADERS 
    BASE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}
    FILES 
        editorcore.h
)

target_link_libraries(editorcore
    gapbuffer
    display
    iohandler
    cmdparser
    cmdrunner
    filemanager
    iohandler
    editorstate
    cursorsyncer
    ${CURSES_LIBRARIES} tinfo
)

