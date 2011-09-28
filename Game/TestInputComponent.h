#pragma once
#include "InputComponent.h"

class Window;

class TestInputComponent :
    public InputComponent
{
public:
    TestInputComponent(void);
    ~TestInputComponent(void);

    void keyboardHandler(unsigned char key);

};

