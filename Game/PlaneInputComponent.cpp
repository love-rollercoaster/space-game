#include "PlaneInputComponent.h"
#include "Camera.h"
#include "Plane.h"

void PlaneInputComponent::registerInputHandlers()
{
    InputComponent::KeyboardInputHandler arrowKeyHandler = MAKE_KEYBOARD_INPUT_HANDLER(PlaneInputComponent::arrowKeyHandler);

    registerInputHandler(VK_LEFT,  arrowKeyHandler);
    registerInputHandler(VK_RIGHT, arrowKeyHandler);
    registerInputHandler(VK_DOWN,  arrowKeyHandler);
    registerInputHandler(VK_UP,  arrowKeyHandler);
    registerInputHandler('W', arrowKeyHandler);
    registerInputHandler('S', arrowKeyHandler);
    registerInputHandler('A', arrowKeyHandler);
    registerInputHandler('D', arrowKeyHandler);
}

void PlaneInputComponent::arrowKeyHandler( unsigned char key )
{
    MoveableGameObject *plane = dynamic_cast<MoveableGameObject*>(gameObject);

    switch(key)
    {
    case VK_LEFT:
        plane->yaw(D3DXToRadian(-1.0f));
        break;
    case VK_RIGHT:
        plane->yaw(D3DXToRadian(1.0f));
        break;
    case VK_DOWN:
        plane->pitch(D3DXToRadian(-1.0f));
        break;
    case VK_UP:
        plane->pitch(D3DXToRadian(1.0f));
        break;
    case 'W':
        plane->changeSpeedBy(50.0f);
        break;
    case 'S':
        plane->changeSpeedBy(-50.0f);
        break;
    case 'A':
        plane->roll(D3DXToRadian(2.0f));
        break;
    case 'D':
        plane->roll(D3DXToRadian(-2.0f));
        break;
    }
}