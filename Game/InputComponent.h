#pragma once

#include <time.h>

class GameObject;
class InputSystem;
class Window;
class Point;

#define KEYBOARD_INPUT_HANDLER(derivedClassName, methodName) \
    reinterpret_cast<KeyboardInputHandler>(&derivedClassName::methodName)

class InputComponent
{
public:
    InputComponent();
    virtual ~InputComponent() = 0;

    static void SetInputSystem(InputSystem *inputSystem);
    void init(GameObject *gameObject);

    typedef long (InputComponent::*KeyboardInputHandler)(Window&, unsigned char key);
    typedef long (InputComponent::*MouseInputHandler)(Window&, Point point);

    // int getId();

protected:
    GameObject *gameObject;

    // Maybe input handlers should be their own class. Because now, since they can't be
    // identified, you can only remove all of them.
    void registerInputHandler(unsigned char key, KeyboardInputHandler inputHandler);
    void registerInputHandler(MouseInputHandler inputHandler);

    // void deregisterAllInputHandlers();

private:
    static InputSystem *inputSystem;

    // THIS WOULD BE NEEDED (I THINK) FOR DEREGISTERING ALL INPUT HANDLERS
    // static int idSeed;      // Used for registered input handler identification.
    // static int getNextId(); // See InputSystem.
                            // Maybe we could move this to a Component base class
                            // if ids are needed for other components.
    // const int id;
};
