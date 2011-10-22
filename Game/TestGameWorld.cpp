#include "TestGameWorld.h"
#include "GameEngine.h"
#include "GraphicsEngine.h"
#include "FontSystem.h"

#define MESH_COLUMNS   100
#define MESH_ROWS      100
#define MESH_CELL_SIZE 10

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

    initObstacles(gameEngine);
}

void TestGameWorld::update( time_t time )
{
    camera.update(time);
}

void TestGameWorld::draw( GraphicsEngine &graphicsEngine )
{
    for each (GameObject* gameObject in gameObjects) {
        gameObject->draw(graphicsEngine);
    }

    for each (Cube obstacle in obstacles) {
        obstacle.draw(graphicsEngine);
    }
}

void TestGameWorld::initMesh( GameEngine &gameEngine )
{
    meshSurfaceGraphicsComponent.initSurface(MESH_COLUMNS, MESH_ROWS, MESH_CELL_SIZE, MESH_CELL_SIZE);
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
    camera.setIgnoreMaxPitchAngle(true);
    camera.setInvertY(true);

    gameEngine.getGraphicsEngine().setCamera(camera);
}

void TestGameWorld::initObstacles( GameEngine &gameEngine )
{
    buildingGraphicsComponent.init(gameEngine.getGraphicsEngine());

    float yMin = 10.0f;
    float yMax = 100.0f;
    float scaleMin = 20.0f;
    float scaleMax = 70.0f;
    float cubeCreationProbablility = 0.98f;

    for (int i = 0; i < MESH_ROWS; i++) {
        for (int j = 0; j < MESH_COLUMNS; j++) {

            float cubeCreationDice = (float)((double)rand() / (RAND_MAX+1)); // FIXME casting

            if (cubeCreationDice > cubeCreationProbablility) {
                float yPosition = (float)((double)rand() / (RAND_MAX+1) * (yMax - yMin) + yMin);         // FIXME casting
                float scale = (float)((double)rand() / (RAND_MAX+1) * (scaleMin - scaleMax) + scaleMax); // FIXME casting

                float xPosition = (float) i * MESH_ROWS;
                float zPosition = (float) j * MESH_COLUMNS;

                D3DXVECTOR3 position(xPosition, yPosition, zPosition);

                Cube cube;
                cube.setPosition(position);
                cube.setScale(scale, scale*10.0f, scale);
                cube.init(NULL, NULL, &buildingGraphicsComponent);
                obstacles.push_back(cube);
            }
        }
    }
}
