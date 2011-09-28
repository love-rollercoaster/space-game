#include "InputSystem.h"
#include "InputComponent.h"

InputSystem::KeyboardMappings InputSystem::keyboardMappings;
InputSystem::MouseMappings    InputSystem::mouseMappings;

void InputSystem::StaticInit()
{
    InputSystem::InitMessageHandlers();
}

InputSystem::InputSystem(void)
{
}

InputSystem::~InputSystem(void)
{
}

void InputSystem::init(/* Window &window */)
{
    // this->window = &window;

    // TODO: CHANGE THIS PUT IT IN InputCompnents CLASS' init, like graphics comp, engine cascade init
    InputComponent::SetInputSystem(this);
}


void InputSystem::registerInputHandler( InputComponent &inputComponent, unsigned char key, KeyboardInputHandler inputHandler )
{
    InputSystem::keyboardMappings.insert(
        KeyboardMapping(key, KeyboardInputHandlerPair(&inputComponent, inputHandler)));
}

void InputSystem::registerInputHandler( InputComponent &inputComponent, MouseInputHandler inputHandler )
{
    mouseMappings.push_back(MouseInputHandlerPair(&inputComponent, inputHandler));
}

void InputSystem::InitMessageHandlers()
{
    Window::RegisterMessageHandler(WM_KEYDOWN,   InputSystem::HandleKeyboardInput);
    Window::RegisterMessageHandler(WM_MOUSEMOVE, InputSystem::HandleMouseInput);
}

long InputSystem::HandleKeyboardInput( Window &window, HWND hwnd, long wparam, long lparam )
{
    printf("KeyDown!");
    return 0;
}

long InputSystem::HandleMouseInput( Window &window, HWND hwnd, long wparam, long lparam )
{
    return 0;
}