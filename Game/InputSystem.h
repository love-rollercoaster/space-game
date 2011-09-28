#pragma once

#include <utility>
#include <list>
#include <map>

#include "Window.h"
#include "InputComponent.h"

using std::list;
using std::map;
using std::multimap;
using std::pair;

class InputComponent;

// For mouse input here, since we have a ref to Window, we could
// do the conversion from screen to world!

class InputSystem
{
public:
    InputSystem(void);
    ~InputSystem(void);

    // This should probably be somewhere
    struct Point {
        float x;
        float y;
    };

    // void unregisterAllInputHandlersFrom(int inputComponentId);
    static void StaticInit();
    static long HandleKeyboardInput(Window &window, HWND hwnd, long wparam, long lparam);
    static long HandleMouseInput(Window &window, HWND hwnd, long wparam, long lparam);

    void init(/* Window &window */);
    void registerInputHandler(InputComponent &inputComponent, unsigned char key, InputComponent::KeyboardInputHandler inputHandler);
    void registerInputHandler(InputComponent &inputComponent, InputComponent::MouseInputHandler inputHandler);

private:
    static void InitMessageHandlers();

    // Window *window; // May need this later to convert coordinates

    typedef pair<InputComponent*, InputComponent::KeyboardInputHandler>         KeyboardInputHandlerPair;
    typedef pair<InputComponent*, InputComponent::MouseInputHandler>            MouseInputHandlerPair;
    typedef pair<unsigned char, KeyboardInputHandlerPair>       KeyboardMapping;
    typedef multimap<unsigned char, KeyboardInputHandlerPair>   KeyboardMappings;
    typedef list<MouseInputHandlerPair>                         MouseMappings;


    static KeyboardMappings keyboardMappings;
    static MouseMappings    mouseMappings;

};
