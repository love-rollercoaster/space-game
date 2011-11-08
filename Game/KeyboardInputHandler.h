#pragma once

#define MAKE_KEYBOARD_INPUT_HANDLER(function) \
    reinterpret_cast<KeyboardInputCallback>(&function)

class InputSystem;

class KeyboardInputHandler
{
public:
    typedef void (KeyboardInputHandler::*KeyboardInputCallback)(unsigned char key);


    static void SetInputSystem(InputSystem* inputSystem);
    virtual void init();

protected:
    // This is where you do all your registerHandler calls.
    virtual void registerKeyboardInputCallbacks() = 0;
    void registerCallback(unsigned char key, KeyboardInputCallback keyboardInputHandler);

private:
    static InputSystem* inputSystem;
};

