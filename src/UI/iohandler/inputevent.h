#include "inputtype.h"

#ifndef INPUT_EVENT
#define INPUT_EVENT

struct InputEvent{
    InputType type;
    int input_ch;
};

#endif