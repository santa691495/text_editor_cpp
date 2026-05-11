add_executable(app main.cpp)

target_link_libraries( app
    gapbuffer
    display
    iohandler
    cmdparser
    cmdrunner
    filemanager
    editorstate
    cursorsyncer
    editorcore
    ${CURSES_LIBRARIES} tinfo
)   

target_compile_options(app PRIVATE 
    -g
    -O0
)