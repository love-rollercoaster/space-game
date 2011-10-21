#pragma once

#include <time.h>
#include "Window.h"

class GameObject;
class InputSystem;
class Point;

#define MAKE_KEYBOARD_INPUT_HANDLER(function) \
    reinterpret_cast<KeyboardInputHandler>(&function)

#define MAKE_MOUSE_INPUT_HANDLER(function) \
    reinterpret_cast<MouseInputHandler>(&function)

// 100x points if you can get Keyboard and mouse input handlers
// the same type.

// You must call init on the object instance because it is the
// function which registers all input handlers with the input
// system.

class InputComponent
{
public:
    static void SetInputSystem(InputSystem *inputSystem);

    virtual ~InputComponent() {}

    typedef void (InputComponent::*KeyboardInputHandler)(Window&, unsigned char key);
    typedef void (InputComponent::*MouseInputHandler)(Window&, Point point);

    void init();
    void init(GameObject *gameObject);

protected:
    // This is where you do all your registerInputHandler calls.
    virtual void registerInputHandlers() = 0;

    GameObject *gameObject;
    void registerInputHandler(unsigned char key, KeyboardInputHandler inputHandler);
    void registerInputHandler(MouseInputHandler inputHandler);

private:
    static InputSystem *inputSystem;
};
