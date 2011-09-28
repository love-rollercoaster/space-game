#include "TestGameApp.h"

TestGameApp::TestGameApp(void)
    : GameApp("Space Game")
{
}

TestGameApp::~TestGameApp( void )
{
}

void TestGameApp::init( GameEngine &gameEngine )
{
    // Who kills game objects?
    GameObject* testGameObject = new GameObject();

    testInputComponent.init(testGameObject);
    testGraphicsComponent.init(gameEngine.getGraphicsEngine());

    testGameObject->init(&testInputComponent, NULL, &testGraphicsComponent);
    testGameObject->setPosition(300.0f, 200.0f, 0.0f);

    testGameWorld.init(gameEngine);
    testGameWorld.addGameObject(testGameObject);
}

void TestGameApp::update( time_t time )
{
    testGameWorld.update(time);
}

void TestGameApp::draw(GraphicsEngine &graphicsEngine)
{
    testGameWorld.draw(graphicsEngine);
}
