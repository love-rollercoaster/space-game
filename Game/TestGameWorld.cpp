#include "TestGameWorld.h"
#include "GameEngine.h"
#include "GraphicsEngine.h"
#include "AsteroidGraphicsComponent.h"
#include "BuildingGraphicsComponent.h"
#include "SpaceshipGraphicsComponent.h"

#define MESH_COLUMNS   100
#define MESH_ROWS      100
#define MESH_CELL_SIZE 10

#define EARTH_POSITION D3DXVECTOR3(-0.3f,0,-1) // fixme
// temporary
#define RANDOM(lowerBound, upperBound) (float)((double)rand() / (RAND_MAX+1) * (upperBound - lowerBound) + lowerBound)



TestGameWorld::TestGameWorld( void )
    : spaceshipGraphicsComponent(new SpaceshipGraphicsComponent())
    , planeInputComponent(new PlaneInputComponent())
{
}

TestGameWorld::~TestGameWorld( void )
{
}

void TestGameWorld::init( GameEngine &gameEngine )
{
    initSpaceship(gameEngine);
    initAsteroids(gameEngine);

    camera = new FollowCamera(&plane);
    camera->setFarPlane(20000.0f);
    gameEngine.getGraphicsEngine().setCamera(*camera);

    GraphicsEngine &graphicsEngine = gameEngine.getGraphicsEngine();
    spaceshipGraphicsComponent->init(graphicsEngine);
    graphicsEngine.setBackgroundColor(D3DCOLOR_XRGB(0, 6, 8));
    graphicsEngine.enableFog(camera->getFarPlane() - 1000.0f, camera->getFarPlane());   
}

void TestGameWorld::update( float time )
{
    plane.update(time);
    camera->update(time);

    for each (shared_ptr<Asteroid> asteroid in asteroids) {
        asteroid->update(time);
    }
}

void TestGameWorld::draw( GraphicsEngine &graphicsEngine )
{
    plane.draw(graphicsEngine);
    for each (shared_ptr<Asteroid> asteroid in asteroids) {
        asteroid->draw(graphicsEngine);
    }
}

void TestGameWorld::initSpaceship( GameEngine &gameEngine )
{
    planeInputComponent->init(&plane);
    plane.init(planeInputComponent, NULL, spaceshipGraphicsComponent);
}

void TestGameWorld::initAsteroids( GameEngine &gameEngine )
{
    float yMin = -1000.0f;
    float yMax = 1000.0f;
    float minAsteroidScale = 10.0f;
    float maxAsteroidScale = 150.0f;
    float asteroidCreationProbablility = 0.994f;

    for (int i = 0; i < MESH_ROWS; i++) {
        for (int j = 0; j < MESH_COLUMNS; j++) {

            float asteroidCreationDice = RANDOM(0,1);

            if (asteroidCreationDice > asteroidCreationProbablility) {
                float yAsteroidPosition = RANDOM(yMax, yMin);
                float asteroidScale = RANDOM(minAsteroidScale, maxAsteroidScale);

                float xAsteroidPosition = (float) i * MESH_ROWS;
                float zAsteroidPosition = (float) j * MESH_COLUMNS;

                shared_ptr<Asteroid> asteroid(new Asteroid());

                asteroid->init(gameEngine);
                

                shared_ptr<MoveableGameObject> asteroidRepresentation = asteroid->getGameObjectRepresentation();
                
                asteroidRepresentation->setScale(asteroidScale, asteroidScale, asteroidScale);
                
                D3DXVECTOR3 asteroidPosition = D3DXVECTOR3(xAsteroidPosition, yAsteroidPosition, zAsteroidPosition);

                asteroidRepresentation->yaw(D3DXToRadian(RANDOM(0, 360)));
                asteroidRepresentation->pitch(D3DXToRadian(RANDOM(0, 360)));
                asteroidRepresentation->roll(D3DXToRadian(RANDOM(0, 360)));
                asteroidRepresentation->setPitchRotationSpeed(RANDOM(0, -0.3f));
                asteroidRepresentation->setRollRotationSpeed(RANDOM(0, -0.3f));
                asteroidRepresentation->setYawRotationSpeed(RANDOM(0, -0.3f));
                asteroidRepresentation->setPosition(asteroidPosition);
                asteroidRepresentation->setFixedDirection(true);
                asteroidRepresentation->setDirection(EARTH_POSITION);
                asteroidRepresentation->setSpeed(RANDOM(75, 400));

                asteroids.push_back(asteroid);
            }
        }
    }
}
