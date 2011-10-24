#include "TestGameWorld.h"
#include "GameEngine.h"
#include "GraphicsEngine.h"
#include "AsteroidGraphicsComponent.h"
#include "BuildingGraphicsComponent.h"
#include "SpaceshipGraphicsComponent.h"

#define MESH_COLUMNS   100
#define MESH_ROWS      100
#define MESH_CELL_SIZE 10

TestGameWorld::TestGameWorld( void )
    : moveableGameObjectGraphicsComponent(new AsteroidGraphicsComponent())
    , spaceshipGraphicsComponent(new SpaceshipGraphicsComponent())
{
}

TestGameWorld::~TestGameWorld( void )
{
    delete spaceshipGraphicsComponent;
    delete moveableGameObjectGraphicsComponent;
}

void TestGameWorld::init( GameEngine &gameEngine )
{
    initCamera(gameEngine);
    initPlane(gameEngine);
    // initMesh(gameEngine);
    initMoveableGameObjects(gameEngine);

    camera = new FollowCamera(&plane);
    gameEngine.getGraphicsEngine().setCamera(*camera);

    GraphicsEngine &graphicsEngine = gameEngine.getGraphicsEngine();
    spaceshipGraphicsComponent->init(graphicsEngine);
    graphicsEngine.setBackgroundColor(D3DCOLOR_XRGB(0, 6, 8));
    graphicsEngine.enableFog(camera->getFarPlane() - 1000.0f, camera->getFarPlane());   
}

void TestGameWorld::update( float time )
{
    camera->update(time);
    for each (GameObject* gameObject in gameObjects) {
        gameObject->update(time);
    }
}

void TestGameWorld::draw( GraphicsEngine &graphicsEngine )
{
    for each (GameObject* gameObject in gameObjects) {
        gameObject->draw(graphicsEngine);
    }
}

void TestGameWorld::initMesh( GameEngine &gameEngine )
{
    GameObject *mesh = new GameObject();
    meshSurfaceGraphicsComponent.initSurface(MESH_COLUMNS, MESH_ROWS, MESH_CELL_SIZE, MESH_CELL_SIZE);
    meshSurfaceGraphicsComponent.init(gameEngine.getGraphicsEngine());
    mesh->init(NULL, NULL, &meshSurfaceGraphicsComponent);

    addGameObject(mesh);
}

void TestGameWorld::initPlane( GameEngine &gameEngine )
{
    planeInputComponent.init(&plane);
    plane.init(&planeInputComponent, NULL, spaceshipGraphicsComponent);
    addGameObject(&plane); //crash during destruction
}

void TestGameWorld::initCamera( GameEngine &gameEngine )
{
/*    D3DXVECTOR3 position(5000.0f, 100.0f, 5000.0f);

    camera.setPosition(position);
    camera.setIgnoreMaxPitchAngle(true);
    camera.setInvertY(true);
    camera.createProjectionMatrix(D3DXToRadian(45), 1.3f, 1.0f, 5000.0f);

    gameEngine.getGraphicsEngine().setCamera(camera);
    */
}

void TestGameWorld::initMoveableGameObjects( GameEngine &gameEngine )
{
    moveableGameObjectGraphicsComponent->init(gameEngine.getGraphicsEngine());

    float yMin = -1000.0f;
    float yMax = 1000.0f;
    float scaleMin = 10.0f;
    float scaleMax = 150.0f;
    float cubeCreationProbablility = 0.99f;

    for (int i = 0; i < MESH_ROWS; i++) {
        for (int j = 0; j < MESH_COLUMNS; j++) {

            float cubeCreationDice = (float)((double)rand() / (RAND_MAX+1)); // FIXME casting

            if (cubeCreationDice > cubeCreationProbablility) {
                float yPosition = (float)((double)rand() / (RAND_MAX+1) * (yMax - yMin) + yMin);         // FIXME casting
                float scale = (float)((double)rand() / (RAND_MAX+1) * (scaleMin - scaleMax) + scaleMax); // FIXME casting

                float xPosition = (float) i * MESH_ROWS;
                float zPosition = (float) j * MESH_COLUMNS;

                MoveableGameObject *moveableGameObject = new MoveableGameObject();
                moveableGameObject->setPosition(D3DXVECTOR3(xPosition, yPosition, zPosition));

                if (((double)rand() / (RAND_MAX+1) * 2.0f) > 1) {
                    moveableGameObject->setScale(100.0f, 100.0f, 100.0f);
                    moveableGameObject->init(NULL, NULL, spaceshipGraphicsComponent);
                } else {
                    moveableGameObject->setScale(scale, scale, scale);
                    moveableGameObject->init(NULL, NULL, moveableGameObjectGraphicsComponent);
                }

                moveableGameObjects.push_back(moveableGameObject);
                addGameObject(moveableGameObject);
            }
        }
    }
}
