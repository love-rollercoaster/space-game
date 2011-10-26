#pragma once

#include <time.h>
#include "Window.h"
#include "KeyboardInputHandler.h"

class GameObject;

class InputComponent
    : public KeyboardInputHandler
{
public:
    virtual ~InputComponent() {}
    virtual void init(GameObject *gameObject);

protected:
    GameObject *gameObject;
    virtual void registerKeyboardInputCallbacks() = 0;
};
