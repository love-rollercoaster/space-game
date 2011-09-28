#pragma once
#include "InputComponent.h"
#include "Window.h"


class TestInputComponent :
    public InputComponent
{
public:
    TestInputComponent(void);
    ~TestInputComponent(void);

    long leftArrowHandler(Window &window, unsigned char key);
    void registerInputHandlers();
};
