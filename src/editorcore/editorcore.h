#include "display.h"
#include "iohandler.h"
#include "cmdparser.h"
#include "cmdrunner.h"
#include "filemanager.h"
#include "editorstate.h"
#include "cursorsyncer.h"
#include "gapbuffer.h"
#include <ncurses.h>    
#include <string>

#ifndef EDITOR_CORE
#define EDITOR_CORE

class EditorCore {

    private:
        Display& dspl;
        IOHandler& io;
        GapBuffer& gbuffer;
        FileManager& fm;
        EditorState& state;
        CommandParser& cmdparser;
        CommandRunner cmdrunner { CommandRunner(fm, gbuffer, state.running) };
        CursorSyncer cursorsync { CursorSyncer(gbuffer, dspl) };

    public:
        EditorCore(
            Display& dspl,
            IOHandler& io,
            CommandParser& cmdparser,
            FileManager& fm,
            GapBuffer& gbuffer,
            EditorState& state
        ); 

        void run(); 
        void run_cmd_loop();
        void run_buffer_loop();

    private:
        void process_input_event(InputEvent& input);
};

#endif
