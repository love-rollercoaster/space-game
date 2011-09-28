#include "TestInputComponent.h"


TestInputComponent::TestInputComponent(void)
{
}

TestInputComponent::~TestInputComponent(void)
{
}

long TestInputComponent::leftArrowHandler( Window &window, unsigned char key )
{
    printf("[TestInputComponent]: Received input!\n");
    return 0;
}

void TestInputComponent::registerInputHandlers()
{
    registerInputHandler(VK_LEFT, MAKE_KEYBOARD_INPUT_HANDLER(TestInputComponent::leftArrowHandler));
}
