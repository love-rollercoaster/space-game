#pragma once

#include <windows.h>
#include <string>
#include <tchar.h>

using std::string;

class Window
{
public:
    Window(string title, HINSTANCE currentInstance, DWORD style, int width, int height);
    ~Window(void);

    static LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

    void show();
    HWND getWindowHandle();

private:
    string className;

    HDC hdc;
    HWND windowHandle;
    WNDCLASSEX windowClass;

    void initializeWindowClass(HINSTANCE currentInstance, DWORD style);
    void registerWindowClass();
    void createWindow(HINSTANCE currentInstance, string title, int width, int height);
};
