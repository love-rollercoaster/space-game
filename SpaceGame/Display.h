#pragma once

#include "windows.h"

class Display
{
public:
    Display(void);
    ~Display(void);

private:
    HWND window;
    RECT viewport;
    int targetFramerate;
    bool fullscreen;
};