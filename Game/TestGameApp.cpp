#include "TestGameApp.h"
#include "Block.h"
#include "GameBoard.h"
#include "FontSystem.h"
#include <sstream>

using std::stringstream;

#define UPDATE_INTERVAL 80
#define BOARD_WIDTH 8
#define BOARD_HEIGHT 12

TestGameApp::TestGameApp(void)
    : GameApp("Nicolas Porter COMP3501 AS01 - Tetris")
	, gameBoard(BOARD_WIDTH,BOARD_HEIGHT)
{
}

TestGameApp::~TestGameApp( void )
{
}

void TestGameApp::init( GameEngine &gameEngine )
{
	gameBoard.init(gameEngine);
	gameBoardInputComponent.init(&gameBoard);
}

void TestGameApp::update( time_t time )
{	
	static int counter = 0;
	if ((counter++) == UPDATE_INTERVAL) {
		counter = 0;
		gameBoard.update(time);
	}
}

void TestGameApp::draw(GraphicsEngine &graphicsEngine)
{
    gameBoard.draw(graphicsEngine);
	
	stringstream scoreText;

	scoreText << "Score: " << gameBoard.getScore();

	FontSystem::DrawText(scoreText.str().c_str(), 10, 10, D3DCOLOR_XRGB(255,255,255));
}
