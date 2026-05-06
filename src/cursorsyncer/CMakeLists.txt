add_library(cursorsyncer)

target_sources(cursorsyncer 
    PRIVATE 
        cursorsyncer.cpp

    PUBLIC  
        FILE_SET HEADERS 
        BASE_DIRS
            ${CMAKE_CURRENT_SOURCE_DIR}
        FILES 
            cursorsyncer.h
)

target_link_libraries( cursorsyncer
    display
    gapbuffer
)