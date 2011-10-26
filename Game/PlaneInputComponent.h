#pragma once

#include "InputComponent.h"
#include "MoveableGameObject.h"

class Plane;

class PlaneInputComponent
    : public InputComponent
{
public:
    virtual void registerKeyboardInputCallbacks();
    void arrowKeyHandler( unsigned char key );

private:
    Plane *plane;
};

