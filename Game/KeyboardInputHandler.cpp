#include "KeyboardInputHandler.h"
#include "InputSystem.h"
#include "Log.h"

InputSystem* KeyboardInputHandler::inputSystem = nullptr;

void KeyboardInputHandler::SetInputSystem( InputSystem* inputSystem )
{
    KeyboardInputHandler::inputSystem = inputSystem;
}

// TODO: input system pointer should be passed in here
void KeyboardInputHandler::init()
{
    if (inputSystem == nullptr) {
        ERR("Input system needs to be set before using keyboard input handlers!");
    }

    registerKeyboardInputCallbacks();
}

void KeyboardInputHandler::registerCallback( unsigned char key, KeyboardInputCallback callback )
{
    KeyboardInputHandler::inputSystem->registerInputCallback( key, *this, callback);
}