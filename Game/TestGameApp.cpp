#include "TestGameApp.h"

TestGameApp::TestGameApp(void)
    : GameApp("Space Game")
{
}

void TestGameApp::init( GameEngine &gameEngine )
{
    testGameWorld.init(gameEngine);
}

void TestGameApp::update( time_t time )
{
    testGameWorld.update(time);
}

void TestGameApp::draw(GraphicsEngine &graphicsEngine)
{
    testGameWorld.draw(graphicsEngine);
}


