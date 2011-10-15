#pragma once

#include "GameApp.h"
#include "GameBoard.h"
#include "GameBoardInputComponent.h"

class TestGameApp : public GameApp
{
public:
    TestGameApp(void);
    ~TestGameApp(void);

    void init(GameEngine &gameEngine);
    void update(time_t time);
    void draw(GraphicsEngine &graphicsEngine);

private:
	GameBoard gameBoard;
    GameBoardInputComponent gameBoardInputComponent;

    void initComponents(GameEngine &gameEngine);
    void initGraphicsComponents(GraphicsEngine &graphicsEngine);
};

