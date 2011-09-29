#pragma once

#include <d3dx9.h>
#include "InputComponent.h"
#include "GameObject.h"

class TestInputComponent :
    public InputComponent
{
public:
    TestInputComponent(void);
    ~TestInputComponent(void);

    void arrowKeyHandler(Window &window, unsigned char key);
    void spaceKeyHandler(Window &window, unsigned char key);

    void registerInputHandlers();
};
