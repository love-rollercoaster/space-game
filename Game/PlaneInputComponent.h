#pragma once

#include "InputComponent.h"

class Plane;

class PlaneInputComponent
    : public InputComponent
{
public:
    virtual void registerInputHandlers();
    void arrowKeyHandler( unsigned char key );

private:
    Plane *plane;
};

