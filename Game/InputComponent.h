#pragma once

#include <time.h>

class GameObject;
class InputSystem;
class Window;
class Point;

#define MAKE_KEYBOARD_INPUT_HANDLER(function) \
    reinterpret_cast<KeyboardInputHandler>(&function)

#define MAKE_MOUSE_INPUT_HANDLER(function) \
    reinterpret_cast<MouseInputHandler>(&function)

// 100x points if you can get Keyboard and mouse input handlers
// the same type.

class InputComponent
{
public:
    InputComponent();
    virtual ~InputComponent() = 0;

    static void SetInputSystem(InputSystem *inputSystem);
    void init(GameObject *gameObject);

    typedef long (InputComponent::*KeyboardInputHandler)(Window&, unsigned char key);
    typedef long (InputComponent::*MouseInputHandler)(Window&, Point point);

protected:
    GameObject *gameObject;

    void registerInputHandler(unsigned char key, KeyboardInputHandler inputHandler);
    void registerInputHandler(MouseInputHandler inputHandler);

private:
    static InputSystem *inputSystem;
};
