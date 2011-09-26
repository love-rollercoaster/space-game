#include "TestGameWorld.h"

TestGameWorld::TestGameWorld(void)
    : triangle(NULL, NULL, &testGraphicsComponent)
{
}


TestGameWorld::~TestGameWorld(void)
{
}

void TestGameWorld::init( GameEngine &gameEngine )
{
    testGraphicsComponent.init(gameEngine.getGraphicsEngine());
}

void TestGameWorld::update( time_t time )
{

}

void TestGameWorld::draw( GraphicsEngine &graphicsEngine )
{
    triangle.draw(graphicsEngine);
}
