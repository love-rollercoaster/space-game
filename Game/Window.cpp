#include "Window.h"

HWND Window::hwnd = NULL;
Window::MessageMap Window::MessageHandlers;

Window::Window(void)
{
}

Window::~Window(void)
{
}

void Window::init(HINSTANCE hInstance, string title, int width, int height)
{
    this->width = width;
    this->height = height;

    TCHAR* className = "win32app";
    WNDCLASSEX windowClass;
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.lpfnWndProc    = Window::MessageRouter;
    windowClass.cbClsExtra     = 0;
    windowClass.cbWndExtra     = 0;
    windowClass.hInstance      = hInstance;
    windowClass.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    windowClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
    windowClass.lpszMenuName   = NULL;
    windowClass.lpszClassName  = className;
    windowClass.hIconSm        = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    windowClass.style          = CS_HREDRAW | CS_VREDRAW;
    windowClass.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);

    if (!RegisterClassEx(&windowClass)) {
        // throw here
    }

    HWND hwnd = CreateWindow(className, 
                             title.c_str(),
                             WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                             CW_USEDEFAULT, CW_USEDEFAULT,
                             width,
                             height,
                             NULL,
                             NULL,
                             hInstance,
                             this); // retrieved by calling RetrieveWindowInstanceFromWindowCreationData

    if (!hwnd) {
        // throw here
    }
}

LRESULT CALLBACK Window::MessageRouter(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    Window *wnd = NULL;

    switch(message)
    {
    case WM_NCCREATE:
        wnd = Window::RetrieveWindowInstanceFromWindowCreationData(hwnd, lparam);
        Window::AssociateWindowInstanceFromWindowCreationData(hwnd, wnd);
        break;
    default:
        wnd = reinterpret_cast<Window *>(GetWindowLong(hwnd, GWL_USERDATA));
    }

    if (wnd)
    {
        MessageIterator messageIterator;
        messageIterator = MessageHandlers.find(message);

        if (messageIterator != MessageHandlers.end()) {
            return (messageIterator->second)((*wnd), hwnd, wparam, lparam);
        }
    }

    return ::DefWindowProc(hwnd, message, wparam, lparam);
}

Window::MessageHandler Window::RegisterMessageHandler(long message, MessageHandler handler)
{
    MessageHandler messageHandler = NULL;
    MessageIterator it = MessageHandlers.find(message);
    
    if(it != MessageHandlers.end()) {
        messageHandler = it->second;
    }

    MessageHandlers.insert(std::pair<long, MessageHandler>(message, handler));

    return messageHandler;
}

HWND Window::GetHandle()
{
    return Window::hwnd;
}

void Window::SetHWND( HWND hwnd )
{
    Window::hwnd = hwnd;
}

void Window::ShowWindow( int nCmdShow )
{
    ::ShowWindow(Window::hwnd, nCmdShow);
}

int Window::getWidth()
{
    return width;
}

int Window::getHeight()
{
    return height;
}

Window* Window::RetrieveWindowInstanceFromWindowCreationData( HWND hwnd, LPARAM lparam )
{
    return reinterpret_cast<Window *>(((LPCREATESTRUCT)lparam)->lpCreateParams);
}

void Window::AssociateWindowInstanceFromWindowCreationData( HWND hwnd, Window *wnd )
{
    ::SetWindowLong(hwnd, GWL_USERDATA, reinterpret_cast<long>(wnd));
    Window::SetHWND(hwnd);
}