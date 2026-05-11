#include "display.h"
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

void EditorCore::run_cmd_loop(){
    std::string cmd_input_str;
    dspl.render_cmd_mode();

    while(state.cmd_mode){
        InputEvent input = io.get_input();

        if(input.input_ch != '\n'){
            cmd_input_str += input.input_ch;
            continue;
        }

        CommandObject cmd = cmdparser.parse(cmd_input_str);
        CmdStatusObject cmd_status = cmdrunner.run(cmd);

        if(cmd_status.success && cmd_status.cmd_type == CmdType::read){
            cursorsync.calibrate_new_buffer();
        }

        state.cmd_mode = false;
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
