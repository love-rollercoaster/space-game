#include "TestGameApp.h"

TestGameApp::TestGameApp(void)
    : GameApp("Game")
{
}

TestGameApp::~TestGameApp( void )
{
}

void TestGameApp::init( GameEngine &gameEngine )
{
    graphicsComponent.init(gameEngine.getGraphicsEngine());
    gameObject.init(NULL, NULL, &graphicsComponent);
    gameWorld.init(gameEngine);
    gameWorld.addGameObject(&gameObject);
}

void TestGameApp::update( time_t time )
{
    gameWorld.update(time);
}

void TestGameApp::draw( GraphicsEngine &graphicsEngine )
{
    gameWorld.draw(graphicsEngine);
}
