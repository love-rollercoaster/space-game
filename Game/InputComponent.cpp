#include "InputComponent.h"
#include "InputSystem.h"

//int InputComponent::idSeed = 0;
InputSystem* InputComponent::inputSystem = NULL;
/*
int InputComponent::getNextId()
{
    return idSeed++;
}
*/
void InputComponent::SetInputSystem( InputSystem *inputSystem )
{
    InputComponent::inputSystem = inputSystem;
}

InputComponent::InputComponent()
    // : id(InputComponent::getNextId())
{

}

InputComponent::~InputComponent()
{

}

// Get input system passed in here yo
void InputComponent::init( GameObject *gameObject )
{
    this->gameObject = gameObject;
}

void InputComponent::registerInputHandler( unsigned char key, KeyboardInputHandler inputHandler )
{
    InputComponent::inputSystem->registerInputHandler(*this, key, inputHandler);
}

void InputComponent::registerInputHandler( MouseInputHandler inputHandler )
{
    InputComponent::inputSystem->registerInputHandler(*this, inputHandler);
}