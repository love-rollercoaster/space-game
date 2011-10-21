#include "TestGameWorld.h"
#include "FontSystem.h"

TestGameWorld::TestGameWorld(void)
{
}

TestGameWorld::~TestGameWorld(void)
{
}

void TestGameWorld::init(GameEngine &gameEngine)
{
    D3DXVECTOR3 position(5000, 100, 5000);
    camera.setPosition(position);
    position.x += 10;
    position.z += 10;
    camera.setLookAtPoint(position);

    gameEngine.getGraphicsEngine().setCamera(camera);
    gameEngine.getGraphicsEngine().setBackgroundColor(D3DCOLOR_XRGB(2,32,22));
}

void TestGameWorld::update( time_t time )
{
    camera.update();
}

void TestGameWorld::draw( GraphicsEngine &graphicsEngine )
{
    for each (GameObject* gameObject in gameObjects) {
        gameObject->draw(graphicsEngine);
    }

    int x = 10;
    int xIncrement = 150;
    
    static char buffer[255];

    D3DXVECTOR3 vector = *camera.getPosition();
    sprintf_s(buffer, "Position\nx: %f\ny: %f\nz: %f", vector.x, vector.y, vector.z);
    FontSystem::DrawText(buffer, 10, 10, D3DCOLOR_XRGB(255,255,255));
}