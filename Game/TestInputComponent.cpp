#include "TestInputComponent.h"
#include "BlockGroup.h"

TestInputComponent::TestInputComponent(void)
{
}

TestInputComponent::~TestInputComponent(void)
{
}

void TestInputComponent::registerInputHandlers()
{
    InputComponent::KeyboardInputHandler arrowKeyHandler = MAKE_KEYBOARD_INPUT_HANDLER(TestInputComponent::arrowKeyHandler);
    InputComponent::KeyboardInputHandler spaceKeyHandler = MAKE_KEYBOARD_INPUT_HANDLER(TestInputComponent::spaceKeyHandler);

    registerInputHandler(VK_LEFT,  arrowKeyHandler);
    registerInputHandler(VK_RIGHT, arrowKeyHandler);
    registerInputHandler(VK_UP,    arrowKeyHandler);
    registerInputHandler(VK_DOWN,  arrowKeyHandler);

    registerInputHandler(VK_SPACE, spaceKeyHandler);
}

void TestInputComponent::arrowKeyHandler( Window &window, unsigned char key )
{
    BlockGroup *blockGroup = dynamic_cast<BlockGroup*>(gameObject);
    Block::Position newPosition = blockGroup->getPosition();

    switch(key)
    {
    case VK_LEFT:
        newPosition.x -= 1;
        break;
    case VK_RIGHT:
        newPosition.x += 1;
        break;
    case VK_UP:
        newPosition.y -= 1;
        break;
    case VK_DOWN:
        newPosition.y += 1;
        break;
    }

    blockGroup->setPosition(newPosition);
}

void TestInputComponent::spaceKeyHandler( Window &window, unsigned char key )
{
    BlockGroup *blockGroup = dynamic_cast<BlockGroup*>(gameObject);
    blockGroup->cycleOrientation();
}
