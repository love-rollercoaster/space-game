#pragma once

#include <time.h>
#include "InputSystem.h"

class GameObject;

class InputComponent
{
public:
    InputComponent();
    virtual ~InputComponent() = 0;

    static void SetInputSystem(InputSystem *inputSystem);
    void init(GameObject *gameObject);

    // int getId();

protected:
    GameObject *gameObject;

    // Maybe input handlers should be their own class. Because now, since they can't be
    // identified, you can only remove all of them.
    void registerInputHandler(unsigned char key, InputSystem::KeyboardInputHandler inputHandler);
    void registerInputHandler(InputSystem::MouseInputHandler inputHandler);

    // void deregisterAllInputHandlers();

private:
    // THIS WOULD BE NEEDED (I THINK) FOR DEREGISTERING ALL INPUT HANDLERS
    // static int idSeed;      // Used for registered input handler identification.
    // static int getNextId(); // See InputSystem.
                            // Maybe we could move this to a Component base class
                            // if ids are needed for other components.

    static InputSystem *inputSystem;
    void inputSystemNullCheck();

    // const int id;
};
