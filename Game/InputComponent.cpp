#include "InputComponent.h"

void InputComponent::init( GameObject *gameObject )
{
    KeyboardInputHandler::init();

    this->gameObject = gameObject;
}