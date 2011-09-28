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
    initComponents(gameEngine);

    GameObject* testGameObject = new GameObject();

    testGameObject->init(NULL, NULL, &testGraphicsComponent);
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

void TestGameApp::initComponents( GameEngine &gameEngine )
{
    initGraphicsComponents(gameEngine.getGraphicsEngine());
}

void TestGameApp::initGraphicsComponents( GraphicsEngine &graphicsEngine )
{
    testGraphicsComponent.init(graphicsEngine);
}


