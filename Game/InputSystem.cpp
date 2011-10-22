#include "InputSystem.h"

InputSystem::KeyboardMappings InputSystem::keyboardMappings;
InputSystem::MouseHandlerPairs InputSystem::mouseHandlerPairs;
bool InputSystem::KeysPressed[] = {false};

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

void InputSystem::DispatchInputEvents()
{
    for (int key = 0; key < NUM_OF_KEYS; key++) {
        if (KeysPressed[key]) {
            DispatchMessageToRegisteredHandlers(key);
        }
    }
}

void InputSystem::InitMessageHandlers()
{
    Window::RegisterMessageHandler(WM_KEYDOWN, InputSystem::HandleKeyDown);
    Window::RegisterMessageHandler(WM_KEYUP, InputSystem::HandleKeyUp);
    Window::RegisterMessageHandler(WM_MOUSEMOVE, InputSystem::HandleMouseInput);
}

long InputSystem::HandleKeyDown( Window &window, HWND hwnd, long wparam, long lparam )
{
    unsigned char key = static_cast<unsigned char>(wparam);
    KeysPressed[key] = true;

    DispatchMessageToRegisteredHandlers(key);

    return 0;
}

long InputSystem::HandleKeyUp( Window &window, HWND hwnd, long wparam, long lparam )
{
    unsigned char input = static_cast<unsigned char>(wparam);
    KeysPressed[input] = false;

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

void InputSystem::DispatchMessageToRegisteredHandlers(unsigned char key)
{
    KeyboardHandlerPairs &keyboardHandlerPairs = GetRegisteredHandlersFromKeyboardInput(key);

    for each (KeyboardInputHandlerPair keyboardInputHandlerPair in keyboardHandlerPairs)
    {
        InputComponent *inputComponent = keyboardInputHandlerPair.first;
        InputComponent::KeyboardInputHandler &inputHandler = keyboardInputHandlerPair.second;
        (inputComponent->*inputHandler)(key);
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
