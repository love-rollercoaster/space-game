#include "TestGameWorld.h"
#include "GameEngine.h"
#include "GraphicsEngine.h"
#include "FontSystem.h"

TestGameWorld::TestGameWorld( void )
{
}

TestGameWorld::~TestGameWorld( void )
{
}

void TestGameWorld::init( GameEngine &gameEngine )
{
    initCamera(gameEngine);
    initPlane(gameEngine);
    initMesh(gameEngine);

    plane.setCamera(camera);
    gameEngine.getGraphicsEngine().setBackgroundColor(D3DCOLOR_XRGB(89,176,234));
}

void TestGameWorld::update( time_t time )
{
    
}

void TestGameWorld::draw( GraphicsEngine &graphicsEngine )
{
    camera.update();

    for each (GameObject* gameObject in gameObjects) {
        gameObject->draw(graphicsEngine);
    }

    static char buffer[255];

    D3DXVECTOR3 vector = *camera.getLookDirection();
    sprintf_s(buffer, "Position\nx: %f\ny: %f\nz: %f", vector.x, vector.y, vector.z);
    FontSystem::DrawText(buffer, 10, 10, D3DCOLOR_XRGB(255,255,255));

}

void TestGameWorld::initMesh( GameEngine &gameEngine )
{
    meshSurfaceGraphicsComponent.init(gameEngine.getGraphicsEngine());
    mesh.init(NULL, NULL, &meshSurfaceGraphicsComponent);
    addGameObject(&mesh);
}

void TestGameWorld::initPlane( GameEngine &gameEngine )
{
    planeInputComponent.init(&plane);
    plane.init(&planeInputComponent, NULL, NULL);
}

void TestGameWorld::initCamera( GameEngine &gameEngine )
{
    D3DXVECTOR3 position(5000, 100, 5000);
    camera.setPosition(position);
    position.x += 10;
    position.z += 10;
    camera.setLookAtPoint(position);
    camera.setIgnoreMaxPitchAngle(true);
    camera.setInvertY(true);

    gameEngine.getGraphicsEngine().setCamera(camera);
}
