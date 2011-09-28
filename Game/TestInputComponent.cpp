#include "TestInputComponent.h"

TestInputComponent::TestInputComponent(void)
{
}

TestInputComponent::~TestInputComponent(void)
{
}

void TestInputComponent::registerInputHandlers()
{
    InputComponent::KeyboardInputHandler inputHandler = MAKE_KEYBOARD_INPUT_HANDLER(TestInputComponent::arrowKeyHandler);

    registerInputHandler(VK_LEFT,  inputHandler);
    registerInputHandler(VK_RIGHT, inputHandler);
    registerInputHandler(VK_UP,    inputHandler);
    registerInputHandler(VK_DOWN,  inputHandler);
}

void TestInputComponent::arrowKeyHandler( Window &window, unsigned char key )
{
    D3DVECTOR position = gameObject->getPosition();

    switch(key)
    {
    case VK_LEFT:
        position.x -= 20;
        break;
    case VK_RIGHT:
        position.x += 20;
        break;
    case VK_UP:
        position.y -= 20;
        break;
    case VK_DOWN:
        position.y += 20;
        break;
    }

    gameObject->setPosition(position);
}