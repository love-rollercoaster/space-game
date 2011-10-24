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
    Plane *plane = dynamic_cast<Plane*>(gameObject);
    Camera *camera = plane->getCamera();

    switch(key)
    {
    case VK_LEFT:
        camera->yaw(D3DXToRadian(-1.0f));
        break;
    case VK_RIGHT:
        camera->yaw(D3DXToRadian(1.0f));
        break;
    case VK_DOWN:
        camera->pitch(D3DXToRadian(1.0f));
        break;
    case VK_UP:
        camera->pitch(D3DXToRadian(-1.0f));
        break;
    case 'W':
        camera->changeSpeedBy(1.0f);
        break;
    case 'S':
        camera->changeSpeedBy(-1.0f);
        break;
    case 'A':
        camera->roll(D3DXToRadian(2.0f));
        break;
    case 'D':
        camera->roll(D3DXToRadian(-2.0f));
        break;
    }
}