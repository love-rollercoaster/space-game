#include "GameBoardInputComponent.h"
#include "GameBoard.h"
#include "BlockGroup.h"

GameBoardInputComponent::GameBoardInputComponent(void)
{
}

GameBoardInputComponent::~GameBoardInputComponent(void)
{
}

void GameBoardInputComponent::registerInputHandlers()
{
    InputComponent::KeyboardInputHandler arrowKeyHandler = MAKE_KEYBOARD_INPUT_HANDLER(GameBoardInputComponent::arrowKeyHandler);
    InputComponent::KeyboardInputHandler spaceKeyHandler = MAKE_KEYBOARD_INPUT_HANDLER(GameBoardInputComponent::spaceKeyHandler);

    registerInputHandler(VK_LEFT,  arrowKeyHandler);
    registerInputHandler(VK_RIGHT, arrowKeyHandler);
    registerInputHandler(VK_DOWN,  arrowKeyHandler);

    registerInputHandler(VK_SPACE, spaceKeyHandler);
}

void GameBoardInputComponent::arrowKeyHandler( Window &window, unsigned char key )
{
    GameBoard *gameBoard = dynamic_cast<GameBoard*>(gameObject);

    switch(key)
    {
    case VK_LEFT:
		gameBoard->moveBlockGroupBy(-1, 0);
		break;
    case VK_RIGHT:
        gameBoard->moveBlockGroupBy(1, 0);
        break;
    case VK_DOWN:
        gameBoard->moveBlockGroupBy(0, 1);
        break;
    }
}

void GameBoardInputComponent::spaceKeyHandler( Window &window, unsigned char key )
{
	GameBoard *gameBoard = dynamic_cast<GameBoard*>(gameObject);
	gameBoard->changeBlockOrientation();
}
