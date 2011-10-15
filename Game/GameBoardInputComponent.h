#pragma once

#include <d3dx9.h>
#include "InputComponent.h"
#include "GameObject.h"

class GameBoardInputComponent :
    public InputComponent
{
public:
    GameBoardInputComponent(void);
    ~GameBoardInputComponent(void);

    void arrowKeyHandler(Window &window, unsigned char key);
    void spaceKeyHandler(Window &window, unsigned char key);

    void registerInputHandlers();
};
