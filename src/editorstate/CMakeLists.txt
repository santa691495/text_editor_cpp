add_library(editorstate INTERFACE)
target_include_directories(editorstate INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} )
target_sources(editorstate INTERFACE editorstate.h)

target_link_libraries(editorstate INTERFACE
    ${CURSES_LIBRARIES}
)