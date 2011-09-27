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

    GameObject* triangle1 = new GameObject();
    // GameObject* triangle2 = new GameObject();
    // GameObject* triangle3 = new GameObject();

    triangle1->init(NULL, NULL, &testGraphicsComponent);

    testGameWorld.init(gameEngine);
    testGameWorld.addGameObject(triangle1);
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


