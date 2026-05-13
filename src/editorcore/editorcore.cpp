#include "display.h"
#include "inputtype.h"
#include "iohandler.h"
#include "cmdparser.h"
#include "cmdrunner.h"
#include "filemanager.h"
#include "editorstate.h"
#include "cursorsyncer.h"
#include "gapbuffer.h"
#include "editorcore.h"
#include <ncurses.h>    
#include <string>   

EditorCore::EditorCore(
    Display& dspl,
    IOHandler& io,
    CommandParser& cmdparser,
    FileManager& fm,
    GapBuffer& gbuffer,
    EditorState& state
):
    dspl(dspl),
    io(io),
    cmdparser(cmdparser),
    fm(fm),
    gbuffer(gbuffer),
    state(state)
{}  

void EditorCore::run(){
    while(state.running){
        run_cmd_loop();
        if(!state.running)
            break;
        run_buffer_loop();   
    }
}

void EditorCore::process_cmd_input_event(InputEvent& input, GapBuffer& cmd_mode_buffer){
    CursorSyncer cmd_cursorsync(cmd_mode_buffer, dspl);

    switch(input.type){
        case InputType::character :
            cmd_mode_buffer.insert(input.input_ch);           
            dspl.save_cursor_pos();
            break;

        case InputType::backspace :
            cmd_mode_buffer.backspace();
            dspl.save_cursor_pos();
            break;

        case InputType::arrow_left :
            cmd_cursorsync.move_left();
            dspl.save_cursor_pos();
            break;

        case InputType::arrow_right :
            cmd_cursorsync.move_right();
            dspl.save_cursor_pos();
            break;

        case InputType::ctrl :
            cursorsync.calibrate_new_buffer();
            dspl.save_cursor_pos();

            state.cmd_mode = false;
            break;

        case InputType::enter :
            std::string cmd_string = cmd_mode_buffer.get_text();
            CommandObject cmd = cmdparser.parse(cmd_string);
            CmdStatusObject cmd_status = cmdrunner.run(cmd);

            cursorsync.calibrate_new_buffer();
            dspl.save_cursor_pos();

            state.cmd_mode = false;
            break;
    }
}

//TODO: Make a temporary gap buffer in this loop to allow backspaces :)))
void EditorCore::run_cmd_loop(){
    if(!state.cmd_mode){
        return;
    }

    GapBuffer cmd_mode_buffer;
    dspl.render_cmd_mode();
    dspl.save_cursor_pos();

    while(state.cmd_mode){  
        std::string cmd_buffer_text = cmd_mode_buffer.get_text();
        dspl.render_cmd_mode(cmd_buffer_text);
        dspl.fix_cursor_pos();

        InputEvent input = io.get_input();
        process_cmd_input_event(input, cmd_mode_buffer);
    }

}

void EditorCore::run_buffer_loop(){
    while(!state.cmd_mode){
        std::string buffer_text = gbuffer.get_text();   
        dspl.render_buffer(buffer_text);
        dspl.fix_cursor_pos();

        InputEvent input = io.get_input();
        process_input_event(input);
    }   
}

void EditorCore::process_input_event(InputEvent& input){
    switch (input.type) {

        case InputType::arrow_left:
            cursorsync.move_left();
            dspl.save_cursor_pos();
            break;

        case InputType::arrow_right:
            cursorsync.move_right();
            dspl.save_cursor_pos();
            break;  

        case InputType::arrow_down:
            cursorsync.move_startln_down();
            dspl.save_cursor_pos();
            break;

        case InputType::arrow_up:
            cursorsync.move_startln_up();
            dspl.save_cursor_pos();
            break;

        case InputType::character:
            gbuffer.insert(input.input_ch);
            dspl.save_cursor_pos();
            break;

        case InputType::backspace:
            if(gbuffer.is_at_line_start()){
                gbuffer.backspace();
                cursorsync.calibrate_startln_backspace();
            } else {
                gbuffer.backspace();
            }

            dspl.save_cursor_pos();
            break;

        case InputType::ctrl:
            state.cmd_mode = true;
            break;

        case InputType::enter:
            gbuffer.insert('\n');
            dspl.move_cursor_startln_down();
            dspl.save_cursor_pos();
            break;

        case InputType::unknown:

            break;
        }
}
