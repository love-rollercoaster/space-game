#include "InputSystem.h"
#include "KeyboardInputHandler.h"

InputSystem::KeyboardMappings InputSystem::keyboardMappings;
// InputSystem::MouseHandlerPairs InputSystem::mouseHandlerPairs;
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
    KeyboardInputHandler::SetInputSystem(this);
}

void InputSystem::registerInputCallback( unsigned char key, KeyboardInputHandler &inputComponent, KeyboardInputHandler::KeyboardInputCallback callback )
{
    InputSystem::AddToKeyboardMappings(key, inputComponent, callback);
}

/*
void InputSystem::registerInputHandler( InputComponent &inputComponent, InputComponent::MouseInputHandler inputHandler )
{
    mouseHandlerPairs.push_back(MouseInputHandlerPair(&inputComponent, inputHandler));
}
*/

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
    // Window::RegisterMessageHandler(WM_MOUSEMOVE, InputSystem::HandleMouseInput);
}

long InputSystem::HandleKeyDown( Window &window, HWND hwnd, long wparam, long lparam )
{
    unsigned char key = static_cast<unsigned char>(wparam);
    KeysPressed[key] = true;

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

/*
long InputSystem::HandleMouseInput( Window &window, HWND hwnd, long wparam, long lparam )
{
    return 0;
}
*/

void InputSystem::DispatchMessageToRegisteredHandlers(unsigned char key)
{
    KeyboardHandlerPairs &keyboardHandlerPairs = GetRegisteredHandlersFromKeyboardInput(key);

    for each (KeyboardInputHandlerPair keyboardInputHandlerPair in keyboardHandlerPairs)
    {
        KeyboardInputHandler *keyboardInputHandler = keyboardInputHandlerPair.first;
        KeyboardInputHandler::KeyboardInputCallback &callback = keyboardInputHandlerPair.second;
        (keyboardInputHandler->*callback)(key);    }
}


void InputSystem::AddToKeyboardMappings(unsigned char key, KeyboardInputHandler &inputHandler, KeyboardInputHandler::KeyboardInputCallback callback)
{
    KeyboardMappings::iterator keyboardMappingsIterator = InputSystem::keyboardMappings.find(key);

    if (keyboardMappingsIterator != keyboardMappings.end())
    {
        // adding handler-callback pair to existing list of handlers for that key
        list<KeyboardInputHandlerPair> &keyboardInputHandlerPairs = keyboardMappingsIterator->second;
        keyboardInputHandlerPairs.push_back(KeyboardInputHandlerPair(&inputHandler, callback));
    } 
    else
    {
        // creating a new list of handler-callback pairs for that key and adding the handler
        InputSystem::keyboardMappings.insert(KeyboardMapping(key, list<KeyboardInputHandlerPair>()));
        AddToKeyboardMappings(key, inputHandler, callback);
    }
}
