#include "InputSystem.h"

InputSystem::KeyboardMappings InputSystem::keyboardMappings;
InputSystem::MouseHandlerPairs    InputSystem::mouseHandlerPairs;

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

void InputSystem::registerInputHandler( unsigned char key, InputComponent &inputComponent, InputComponent::KeyboardInputHandler inputHandler )
{
    InputSystem::AddToKeyboardMappings(key, inputComponent, inputHandler);
}

void InputSystem::registerInputHandler( InputComponent &inputComponent, InputComponent::MouseInputHandler inputHandler )
{
    mouseHandlerPairs.push_back(MouseInputHandlerPair(&inputComponent, inputHandler));
}

void InputSystem::InitMessageHandlers()
{
    Window::RegisterMessageHandler(WM_KEYDOWN, InputSystem::HandleKeyboardInput);
    Window::RegisterMessageHandler(WM_MOUSEMOVE, InputSystem::HandleMouseInput);
}

long InputSystem::HandleKeyboardInput( Window &window, HWND hwnd, long wparam, long lparam )
{
    unsigned char input = static_cast<unsigned char>(wparam);
    KeyboardHandlerPairs &keyboardHandlerPairs = GetRegisteredHandlersFromKeyboardInput(input);      
    DispatchMessageToRegisteredHandlers(input, window, keyboardHandlerPairs);

    return 0;
}

InputSystem::KeyboardHandlerPairs InputSystem::GetRegisteredHandlersFromKeyboardInput(unsigned char input) {
    static KeyboardHandlerPairs emptyList;

    KeyboardMappings::iterator keyboardMappingsIterator = keyboardMappings.find(input);

    if (keyboardMappingsIterator != keyboardMappings.end()) {
        return keyboardMappingsIterator->second;
    } else {
        return emptyList;
    }
}

long InputSystem::HandleMouseInput( Window &window, HWND hwnd, long wparam, long lparam )
{
    return 0;
}

void InputSystem::DispatchMessageToRegisteredHandlers(unsigned char key, Window &window, KeyboardHandlerPairs &keyboardHandlerPairs )
{
    for each (KeyboardInputHandlerPair keyboardInputHandlerPair in keyboardHandlerPairs)
    {
        InputComponent *inputComponent = keyboardInputHandlerPair.first;
        InputComponent::KeyboardInputHandler &inputHandler = keyboardInputHandlerPair.second;
        (inputComponent->*inputHandler)(window, key);
    }
}

                                                                                           /* fix this, should not be a member of InputComponent */
void InputSystem::AddToKeyboardMappings(unsigned char key, InputComponent &inputComponent, InputComponent::KeyboardInputHandler inputHandler)
{
    KeyboardMappings::iterator keyboardMappingsIterator = InputSystem::keyboardMappings.find(key);

    if (keyboardMappingsIterator != keyboardMappings.end()) {
        list<KeyboardInputHandlerPair> &keyboardInputHandlerPairs = keyboardMappingsIterator->second;
        keyboardInputHandlerPairs.push_back(KeyboardInputHandlerPair(&inputComponent, inputHandler));
    } 
    else {
        InputSystem::keyboardMappings.insert(KeyboardMapping(key, list<KeyboardInputHandlerPair>()));
        AddToKeyboardMappings(key, inputComponent, inputHandler);
    }
}