#pragma once

#include <windows.h>

// Reference:
// http://www.halcyon.com/~ast/dload/guicon.htm

class Win32Console
{
public:
    Win32Console(void);
    ~Win32Console(void);

    void show();
    void setScrollbackBufferSize(int size);

private:
    void disableXButton();
    void disableXButtonInMenu();
    
    void redirectStreams();
};

