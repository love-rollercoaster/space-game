#include "InputComponent.h"
#include "InputSystem.h"

InputSystem* InputComponent::inputSystem = NULL;

void InputComponent::SetInputSystem( InputSystem *inputSystem )
{
    InputComponent::inputSystem = inputSystem;
}

// TODO: input system should be passed in here
void InputComponent::init()
{
    this->init(NULL);
}

void InputComponent::init( GameObject *gameObject )
{
    this->gameObject = gameObject;
    registerInputHandlers();
}

void InputComponent::registerInputHandler( unsigned char key, KeyboardInputHandler inputHandler )
{
    InputComponent::inputSystem->registerInputHandler( key, *this, inputHandler);
}

void InputComponent::registerInputHandler( MouseInputHandler inputHandler )
{
    InputComponent::inputSystem->registerInputHandler(*this, inputHandler);
}