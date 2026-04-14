#ifndef EDITOR_STATE
#define EDITOR_STATE

class EditorState {
    public:
        //normal
        bool cmd_mode = false;
        bool running = true;
        bool cursor_left_next_refresh = false;
        bool cursor_right_next_refresh = false;
};

#endif 
