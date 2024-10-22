#pragma once

#include <utility>
#include <list>
#include <map>
#include <functional>

#include "Window.h"
#include "KeyboardInputHandler.h"

using std::list;
using std::map;
using std::pair;
using std::tr1::function;

// For mouse input here, since we have a ref to Window, we could
// do the conversion from screen to world!

class InputSystem
{
public:
    InputSystem(void);
    ~InputSystem(void);

    // This should probably be somewhere else
    struct Point {
        float x;
        float y;
    };

    static void StaticInit();
    static long HandleKeyDown(Window &window, HWND hwnd, long wparam, long lparam);
    static long HandleKeyUp(Window &window, HWND hwnd, long wparam, long lparam);
    // static long HandleMouseInput(Window &window, HWND hwnd, long wparam, long lparam);

    void init(/* Window &window */);
    void registerInputCallback(unsigned char key, KeyboardInputHandler &inputHandler, KeyboardInputHandler::KeyboardInputCallback callback);
    // void registerInputHandler(InputComponent &inputComponent, InputComponent::MouseInputHandler inputHandler);

    static void DispatchInputEvents();

private:
    typedef pair<KeyboardInputHandler*, KeyboardInputHandler::KeyboardInputCallback> KeyboardInputHandlerPair;
    typedef list<KeyboardInputHandlerPair>                                           KeyboardHandlerPairs;
    typedef pair<unsigned char, KeyboardHandlerPairs>                                KeyboardMapping;
    typedef  map<unsigned char, KeyboardHandlerPairs>                                KeyboardMappings;

    // typedef pair<InputComponent*, InputComponent::MouseInputHandler>    MouseInputHandlerPair;
    // typedef list<MouseInputHandlerPair>                                 MouseHandlerPairs;

    static KeyboardMappings  keyboardMappings;
    // static MouseHandlerPairs mouseHandlerPairs;

    static const int NUM_OF_KEYS = 256; // Key events are 8-bit chars
    static bool KeysPressed[NUM_OF_KEYS];

    static void InitMessageHandlers();
    static void DispatchMessageToRegisteredHandlers(unsigned char key);
    static KeyboardHandlerPairs GetRegisteredHandlersFromKeyboardInput(unsigned char input);
    static void AddToKeyboardMappings(unsigned char key, KeyboardInputHandler &inputHandler, KeyboardInputHandler::KeyboardInputCallback callback);
};
