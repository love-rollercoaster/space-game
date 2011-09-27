#include "TestGameWorld.h"

TestGameWorld::TestGameWorld()
{
}

TestGameWorld::~TestGameWorld(void)
{
}

void TestGameWorld::init( GameEngine &gameEngine)
{
}

void TestGameWorld::update( time_t time )
{
}

void TestGameWorld::draw( GraphicsEngine &graphicsEngine )
{
    for each (GameObject* gameObject in gameObjects) {
        gameObject->draw(graphicsEngine);
    }
}