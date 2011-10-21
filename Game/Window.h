
#pragma once

#include <windows.h>
#include <string>
#include <tchar.h>
#include <map>

using std::map;
using std::string;

/*
Based on
http://www.gamedev.net/page/resources/_/reference/programming/creating-a-win32-window-wrapper-class-r1810

= HOW TO USE THIS CLASS =================================================================================
1. Instantiate an object.
2. Call the static Initialize method.
   This creates the win32 window.

To handle a message, you need to register a message handler. 
This allows the addition of message handlers at runtime.

Ex.
long DestroyHandler(Window &window, HWND hwnd, long wparam, long lparam) 
{
    ::PostQuitMessage(0);
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    Window window;
    window.Initialize(hInstance, "Hello World", 800, 600);
    window.RegisterMessageHandler(WM_DESTROY, DestroyHandler);
    window.ShowWindow(nCmdShow);
}
*/


class Window
{
public:
    typedef long (*MessageHandler)(Window&, HWND, long, long);

    Window(void);
    ~Window(void);

    static LRESULT CALLBACK MessageRouter(HWND, UINT, WPARAM, LPARAM);
    static HWND GetHandle();
    static void ShowWindow(int nCmdShow);
    static MessageHandler RegisterMessageHandler(long message, MessageHandler handler);

    void init(HINSTANCE hInstance, string title, int width, int height);
    int getWidth();
    int getHeight();

private:
    typedef map<long, MessageHandler> MessageMap;
    typedef MessageMap::iterator MessageIterator;

    // Maybe we should do GetClientRect instead
    int width;
    int height;

    static HWND hwnd;
    static MessageMap MessageHandlers;

    static void SetHWND(HWND);

    static Window* RetrieveWindowInstanceFromWindowCreationData(HWND hwnd, LPARAM lparam);
    static void AssociateWindowInstanceFromWindowCreationData(HWND hwnd, Window *wnd);

};

