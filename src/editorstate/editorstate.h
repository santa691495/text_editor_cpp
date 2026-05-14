#ifndef EDITOR_STATE
#define EDITOR_STATE

class EditorState {
    public:
        //normal
        bool cmd_mode = false;
        bool running = true;
        bool cmd_was_executed = false;
};

#endif 
